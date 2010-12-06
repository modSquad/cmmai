#include <msgQLib.h>
#include <semLib.h>
#include <wdLib.h>
#include "boxManager.h"

static boxState_t	_boxState;
static WDOG_ID		_productStarvationHandlerID = NULL;
static MSG_Q_ID		_boxesQueue = NULL;
static MSG_Q_ID		_eventsQueue = NULL;
static settings_t	*_settings = NULL;
static SEM_ID		_boxHandlingRequest = NULL;


/*--------------------------------------------------*/
/* Private functions */

static BOOL sendBox ( )
{
	if (1/*msgQSend(TODO) == OK*/)
	{
		/*sendEvent(carton déposé)*/
		return TRUE;
	}
	else
	{
		/*sendEvent(file pleine)*/
		return FALSE;
	}
}

static void getBox ( )
{
	if (1/*TODOcarton présent*/)
	{
	}
	else
	{
		/*sendEvent(TODOpas de carton)*/
	}
}

/*--------------------------------------------------*/
/* IT and alarm handlers */

/* TODO : vérifier la signature */
static int ProductStarvationHandler ( )
{
	return 0;
}

/* TODO : vérifier la signature */
static int ProductInflowHandler ( )
{
	return 0;
}

/* TODO : vérifier la signature */
static int EmergencyStopHandler ( )
{
	return 0;
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
	/*TODO:init boxState*/

	/* JOB */
	for ( ; ; )
	{
		BOOL boxError = FALSE;

		semTake(_boxHandlingRequest, WAIT_FOREVER);

		if (_boxState.boxedProductsCount >=
				_settings->productsPerBox)
		{
			boxError = sendBox();
		}

		if (!boxError)
		{
		
			if (_settings->applicationEndRequest)
			{
				/*TODO*/
			}
			else
			{
				getBox();
			}
		}
	}

	/* END */
	/*TODO*/

	return 0; /*TODO*/
}

