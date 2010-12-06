#include <taskLib.h>
#include <msgQLib.h>
#include <semLib.h>
#include <wdLib.h>
#include "boxManager.h"

static const int PRODUCT_STARVATION_DELAY = 5;
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

static BOOL sendBox ( )
{
	boxData_t boxData =
		{
			_settings->batchID,
			_boxState.boxID,
			_boxState.boxedProductsCount,
			_boxState.defectiveProductsCount
		};
	boxesQueueMsg_t boxMsg =
		{
			false,
			boxData
		};
	event_msg_t eventMsg =
		{
			EVT_NONE,
			boxData
		};

	if ( msgQSend(_boxesQueue, &boxMsg, sizeof(boxMsg),
				NO_WAIT, MSG_PRI_NORMAL) == OK )
	{
		eventMsg.event = EVT_BOX_PROCESSED;
		msgQSend(_eventsQueue, &eventMsg, sizeof(eventMsg),
				WAIT_FOREVER, MSG_PRI_NORMAL);

		_settings->batchBoxesCount += 1; /* TODO : copier dans le schéma de conception (oubli) */
		_boxState.boxID += 1;
		_boxState.boxedProductsCount = 0;
		_boxState.defectiveProductsCount = 0;
		_boxState.filling = FALSE;

		return TRUE;
	}
	else
	{
		eventMsg.event = EVT_ERR_FULL_QUEUE;
		msgQSend(_eventsQueue, &eventMsg, sizeof(eventMsg),
				WAIT_FOREVER, MSG_PRI_NORMAL);
		return FALSE;
	}
}

static void startBoxFilling ( )
{
	if (1/*TODO carton présent*/)
	{
		_boxState.filling = TRUE;
		wdStart(_productStarvationHandlerID,
				PRODUCT_STARVATION_DELAY*sysClkRateGet(),
				(FUNCTPTR)ProductStarvationHandler, 0);
		/* TODO ouvrir le clapet */
	}
	else
	{
		event_msg_t eventMsg =
			{
				EVT_ERR_BOX_STARVATION,
				{ /* Box Data */
					_settings->batchID,
					_boxState.boxID,
					_boxState.boxedProductsCount,
					_boxState.defectiveProductsCount
				}
			};
		msgQSend(_eventsQueue, &eventMsg, sizeof(eventMsg),
				WAIT_FOREVER, MSG_PRI_NORMAL);
	}
}

static void stopBoxFilling ( )
{
	/* TODO fermer le clapet  */
	wdCancel(_productStarvationHandlerID);
	_boxState.filling = FALSE;
	/* TODO ajouter & détailler l'écriture dans BoxState dans la conception */
}

static void endTask ( )
{
	boxData_t boxData =
		{
			_settings->batchID,
			_boxState.boxID,
			_boxState.boxedProductsCount,
			_boxState.defectiveProductsCount
		};
	boxesQueueMsg_t boxMsg =
		{
			TRUE,
			boxData
		};
	event_msg_t eventMsg =
		{
			EVT_END_FILLING,
			boxData
		};
	msgQSend(_eventsQueue, &eventMsg, sizeof(eventMsg),
			WAIT_FOREVER, MSG_PRI_NORMAL);
	msgQSend(_boxesQueue, &boxMsg, sizeof(boxMsg),
			WAIT_FOREVER, MSG_PRI_NORMAL);

	taskSuspend(taskIdSelf());
}

/*--------------------------------------------------*/
/* IT and alarm handlers */

/* TODO : vérifier la signature */
static void ProductStarvationHandler ( )
{
	stopBoxFilling();
}

/* TODO : vérifier la signature */
static void ProductInflowHandler ( )
{
	/* TODO : n'utiliser que stopBoxFilling(); , ne pas accéder directement au clapet */
	/* TODO : mettre à jour _boxState.filling si on est à la fin d'un carton */
}

/* TODO : vérifier la signature */
static void EmergencyStopHandler ( )
{
	stopBoxFilling();
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

	/* TODO : fermer le clapet */

	/* JOB */
	for ( ; ; )
	{
		BOOL boxError = FALSE;

		semTake(_boxHandlingRequest, WAIT_FOREVER);

		/* The token can be given while filling a box, when the application end
			is requested by user. In this case, the request is ignored (will be
			processed at the end of the current box)
		*/
		if (!_boxState.filling) /* TODO ajouter ce test dans la conception */
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
					/* TODO : inverser les "if" dans la conception : pas besoin de déclencher une erreur
					de famine de carton si le lot est terminé */
					startBoxFilling();
				}
			}
		}
	}

	/* END */
	endTask();

	return 0;
}

