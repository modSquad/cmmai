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
		STATUS boxPushStatus = OK;

		semTake(_boxHandlingRequest, WAIT_FOREVER);

		if (_boxState.boxedProductsCount >=
				_settings->productsPerBox)
		{
			/*boxPushStatus = msgQSend()*/
		}
		
		if (!_settings->applicationEndRequest)
		{
			/*TODO*/
		}
	}

	/* END */
	/*TODO*/

}
