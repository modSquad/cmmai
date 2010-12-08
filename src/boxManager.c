#include <wdLib.h>
#include <taskLib.h>
#include <msgQLib.h>
#include <semLib.h>
#include <sysLib.h>
#include <stdio.h>
#include "boxManager.h"
#include "devices.h"

#define PRODUCT_STARVATION_DELAY 5
	/* Time, in seconds, after which an error is triggered if no
	 * product was dropped to the machine
	 */

static boxState_t	_boxState;
static WDOG_ID		_productStarvationHandlerID = NULL;
static MSG_Q_ID		_boxesQueue = NULL;
static MSG_Q_ID		_eventsQueue = NULL;
static settings_t	*_settings = NULL;
static SEM_ID		_boxHandlingRequest = NULL;

static void ProductStarvationHandler();

/*--------------------------------------------------*/
/* Private functions */

/* Copy the currently filling box data in the given buffer */
static void getCurrentBoxData (boxData_t* buffer)
{
	buffer->batchID = _settings->batchID;
	buffer->boxID = _boxState.boxID;
	buffer->boxedProducts = _boxState.boxedProductsCount;
	buffer->defectiveProducts = _boxState.defectiveProductsCount;
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

static BOOL sendBox ( )
{
	boxData_t boxData;
	boxesQueueMsg_t boxMsg;
	getCurrentBoxData(&boxMsg.boxData);

	boxMsg.lastMessage = FALSE;
	getCurrentBoxData(&boxMsg.boxData);
	
	if ( msgQSend(_boxesQueue, (char*)&boxMsg, sizeof(boxMsg),
				NO_WAIT, MSG_PRI_NORMAL) == OK )
	{
		sendEvent(EVT_BOX_PROCESSED,&boxData,WAIT_FOREVER);

		_settings->batchBoxesCount += 1;
		_boxState.boxID += 1;
		_boxState.boxedProductsCount = 0;
		_boxState.defectiveProductsCount = 0;
		_boxState.filling = FALSE;

		return TRUE;
	}
	else
	{
		sendEvent(EVT_ERR_FULL_QUEUE,&boxData,WAIT_FOREVER);
		return FALSE;
	}
}

static void startBoxFilling ( )
{
	if (presenceDetected(BOX_PRESENCE_SENSOR))
	{
		_boxState.filling = TRUE;
		wdStart(_productStarvationHandlerID,
				PRODUCT_STARVATION_DELAY*sysClkRateGet(),
				(FUNCPTR)ProductStarvationHandler, 0);
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
	/* TODO ajouter & dÃ©tailler l'Ã©criture dans BoxState dans la conception */
}

static void endTask ( )
{
	boxData_t boxData;
	boxesQueueMsg_t boxMsg;
	getCurrentBoxData(&boxMsg.boxData);

	boxMsg.lastMessage = FALSE;
	getCurrentBoxData(&boxMsg.boxData);
	
	sendEvent(EVT_END_FILLING,&boxData,WAIT_FOREVER);
	msgQSend(_boxesQueue, (char*)&boxMsg, sizeof(boxMsg),
			WAIT_FOREVER, MSG_PRI_NORMAL);

	taskSuspend(taskIdSelf());
}

/*--------------------------------------------------*/
/* IT and alarm handlers */

static void ProductStarvationHandler ( )
{
	boxData_t boxData;
	
	/* A product starvation occured ; we stop the box filling */
	stopBoxFilling();
	
	/* A product starvation occured ; we warn the user */
	getCurrentBoxData(&boxData);
	sendEvent(EVT_ERR_PRODUCT_STARVATION,&boxData,NO_WAIT);
}

static void ProductInflowHandler ( )
{
	if(defectiveProduct(PRODUCT_DEFECT_SENSOR))
	{
		/* The box is full **/
		setValveState(OUTLET_VALVE, CLOSED); /* TODO : modifier le schéma de conception en conséquence */
		_boxState.boxedProductsCount++;
		if(_boxState.boxedProductsCount == _settings->productsPerBox)
		{
			stopBoxFilling();
			if(semGive(_boxHandlingRequest) == ERROR)
			{
				fprintf(stderr, "_boxHandlingRequest : cannot give semaphore\n");
			}
		}
	}
	else /* The product is rejected */
	{
		setValveState(OUTLET_VALVE, OPEN); /* TODO : modifier le schéma de conception en conséquence */
		++_boxState.defectiveProductsCount;
		if(_boxState.defectiveProductsCount == _settings->maxDefectiveProductsPerBox)
			/* TODO : gérer la reprise (utiliser un modulo ?) */
		{
			boxData_t boxData;
			
			stopBoxFilling();
			
			getCurrentBoxData(&boxData);
			sendEvent(EVT_ERR_DEFECTIVE_TRESHOLD_REACHED, &boxData, NO_WAIT);
		}
	}
}


static void EmergencyStopHandler ( )
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
	/* INIT */
	_boxesQueue = boxesQueue;
	_eventsQueue = eventsQueue;
	_settings = settings;
	_boxHandlingRequest = boxHandlingRequest;

	_boxState.boxID = 0;
	_boxState.boxedProductsCount = 0;
	_boxState.defectiveProductsCount = 0;
	_boxState.filling = FALSE;

	setValveState(INLET_VALVE, CLOSED);

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
				boxError = sendBox();
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
	endTask();

	return 0;
}

