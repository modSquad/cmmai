#include <wdLib.h>
#include <taskLib.h>
#include <msgQLib.h>
#include <semLib.h>
#include <sysLib.h>
#include <stdio.h>
#include "boxManager.h"
#include "devices.h"

#define PRODUCT_STARVATION_DELAY 10
	/* Time, in seconds, after which an error is triggered if no
	 * product was dropped to the machine
	 */

static boxState_t	_boxState;
static WDOG_ID		_productStarvationHandlerID = NULL;
static MSG_Q_ID		_boxesQueue = NULL;
static MSG_Q_ID		_eventsQueue = NULL;
static settings_t	*_settings = NULL;
static SEM_ID		_boxHandlingRequest = NULL;

static int ProductStarvationHandler(int);

/*--------------------------------------------------*/
/* Private functions */

/* Copy the currently filling box data in the given buffer */
static void getCurrentBoxData (boxData_t* buffer)
{
	buffer->batchID = _settings->batchID;
	buffer->boxID = _boxState.boxID;
	buffer->boxedProducts = _boxState.boxedProductsCount;
	buffer->defectiveProducts = _boxState.defectiveProductsCount;
	buffer->printer = NO_PRINTER;
}

/* Send an event to the events queue */
static STATUS sendEvent(boxingEvent_t event, const boxData_t* boxData,
		int timeout)
{
	event_msg_t eventMsg;

	eventMsg.event = event;
	eventMsg.boxData = *boxData;
	
	return msgQSend(_eventsQueue, (char*)&eventMsg, sizeof(eventMsg),
			timeout, MSG_PRI_NORMAL);
}

/** Send a box to the print queue
 * @return TRUE if the box was sent, FALSE otherwise.
 */
static BOOL sendBox ( )
{
	boxesQueueMsg_t boxMsg;

	boxMsg.lastMessage = FALSE;
	getCurrentBoxData(&boxMsg.boxData);

	if ( msgQSend(_boxesQueue, (char*)&boxMsg, sizeof(boxMsg),
				NO_WAIT, MSG_PRI_NORMAL) == OK )
	{
		sendEvent(EVT_BOX_PROCESSED,&boxMsg.boxData,WAIT_FOREVER);

		++_settings->batchBoxesCount;
		++_boxState.boxID;
		_boxState.boxedProductsCount = 0;
		_boxState.defectiveProductsCount = 0;
		_boxState.filling = FALSE;

		return TRUE;
	}
	else
	{
		sendEvent(EVT_ERR_FULL_QUEUE,&boxMsg.boxData,WAIT_FOREVER);
		return FALSE;
	}
}

static void startBoxFilling ( )
{
	if (presenceDetected(BOX_PRESENCE_SENSOR))
	{
		_boxState.filling = TRUE;
		
		if (wdStart(_productStarvationHandlerID,
				PRODUCT_STARVATION_DELAY*sysClkRateGet(),
				ProductStarvationHandler, 0/*DUMMY*/) == ERROR)
		{
			perror("Product starvation error: ");
		}
		
		setValveState(INLET_VALVE,OPEN);
	}
	else
	{
		boxData_t boxData;
		getCurrentBoxData(&boxData);
		sendEvent(EVT_ERR_BOX_STARVATION,&boxData,WAIT_FOREVER);
	}
}

static void stopBoxFilling ( )
{
	setValveState(INLET_VALVE,CLOSED);
	wdCancel(_productStarvationHandlerID);
	_boxState.filling = FALSE;
	/* TODO ajouter & détailler l'écriture dans BoxState dans la conception */
}

/*--------------------------------------------------*/
/* IT and alarm handlers */

/* Alarm handler for product starvation
 * 
 */
static int ProductStarvationHandler ( int DUMMY )
{
	boxData_t boxData;
	
	DUMMY=0; /* Unused, we fool the compiler */
	
	/* A product starvation occured ; we stop the box filling */
	stopBoxFilling();
	
	/* A product starvation occured ; we warn the user */
	getCurrentBoxData(&boxData);
	sendEvent(EVT_ERR_PRODUCT_STARVATION,&boxData,NO_WAIT);
}

/* IT Handler for product inflow
 * This function is not static for testing purpose.
 */
/*static*/ void ProductInflowHandler ( )
{
	BOOL defect = defectiveProduct(PRODUCT_DEFECT_SENSOR);

	wdStart(_productStarvationHandlerID, PRODUCT_STARVATION_DELAY*sysClkRateGet(),
			ProductStarvationHandler, 0/*DUMMY*/);
	
	if(!defect)
	{
		setValveState(OUTLET_VALVE, CLOSED);
		_boxState.boxedProductsCount++;
		
		if(_boxState.boxedProductsCount == _settings->productsPerBox)
		{
			/* The box is full */
			stopBoxFilling();
			if(semGive(_boxHandlingRequest) == ERROR)
			{
				fprintf(stderr, "_boxHandlingRequest : cannot give semaphore\n");
			}
		}
	}
	else /* The product is rejected */
	{
		setValveState(OUTLET_VALVE, OPEN);
		++_boxState.defectiveProductsCount;

		/* The number of defective products can exceed
		 * maximum, if user asked to continue after an error occured.
		 * That's why we test the modulo, and not equality.
		 */
		if((_boxState.defectiveProductsCount%_settings->maxDefectiveProductsPerBox)
				== 0)
		{
			boxData_t boxData;
			
			stopBoxFilling();
			
			getCurrentBoxData(&boxData);
			sendEvent(EVT_ERR_DEFECTIVE_TRESHOLD_REACHED, &boxData, NO_WAIT);
		}
	}
	
}

/* IT Handler for emergency stop.
 * This function is not static for testing purpose.
 */
/*static*/ void EmergencyStopHandler ( )
{
	boxData_t boxData;
	
	/* An emergency stop is needed ; we stop the box filling */
	stopBoxFilling();
	
	/* An emergency stop occured ; we warn the user */
	getCurrentBoxData(&boxData);
	sendEvent(EVT_EMERGENCY_STOP,&boxData,NO_WAIT);
}


/*--------------------------------------------------*/
/* Bootstrap */

int boxManager(MSG_Q_ID boxesQueue, MSG_Q_ID eventsQueue,
		settings_t* settings, SEM_ID boxHandlingRequest)
{
	boxesQueueMsg_t boxMsg; /* Used only at the end */

	/* INIT */
	_boxesQueue = boxesQueue;
	_eventsQueue = eventsQueue;
	_settings = settings;
	_boxHandlingRequest = boxHandlingRequest;

	_boxState.boxID = 0;
	_boxState.boxedProductsCount = 0;
	_boxState.defectiveProductsCount = 0;
	_boxState.filling = FALSE;

	_productStarvationHandlerID = wdCreate();

	/* JOB */
	for ( ; ; )
	{
		BOOL boxError = FALSE;

		semTake(_boxHandlingRequest, WAIT_FOREVER);

		/* The token can be given while filling a box, when the application end
			is requested by user. In this case, the request is ignored (will be
			processed at the end of the current box)
		*/
		if (!_boxState.filling)
		{
			if (_boxState.boxedProductsCount >=
					_settings->productsPerBox)
			{
				/* We have a full box. Let's try to send it to the printers */
				boxError = !sendBox();
			}

			if (!boxError)
			{
				/* We're in a clean state ; we can continue dropping products
				 * or stop the application
				 */
				if (_settings->applicationEndRequest)
				{
					break;
				}
				else if (_settings->batchBoxesCount < _settings->batchBoxesAsked)
				{
					startBoxFilling();
				}
			}
		}
	}

	/* END */
	wdDelete(_productStarvationHandlerID);

	boxMsg.lastMessage = FALSE;
	getCurrentBoxData(&boxMsg.boxData);

	sendEvent(EVT_END_FILLING,&boxMsg.boxData,WAIT_FOREVER);
	msgQSend(_boxesQueue, (char*)&boxMsg, sizeof(boxMsg),
			WAIT_FOREVER, MSG_PRI_NORMAL);

	taskSuspend(taskIdSelf());

	return 0;
}

