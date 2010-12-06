#include <msgQLib.h>
#include <semLib.h>
#include <wdLib.h>
#include "boxManager.h"

static boxState_t	_boxState;
static WDOG_ID		_productStarvationHandlerID = NULL;
static MSG_Q_ID		_boxesQueue = NULL; /* TODO : utile ? */
static MSG_Q_ID		_eventsQueue = NULL;
static settings_t	*_settings = NULL;
static SEM_ID		_boxHandlingRequest = NULL;


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
	
	/* TODO : créer une boîte aux lettres correcte pour PrintManager (gestion de la fin de l'appli) */
	if (1/*msgQSend(TODO) == OK*/)
	{
		sendEvent(EVT_BOX_PROCESSED,&boxData); /* TODO : msgQSend ? */
		
		_settings->batchBoxesCount += 1; /* TODO : copier dans le schéma de conception (oubli) */
		_boxState.boxID += 1;
		_boxState.boxedProductsCount = 0;
		_boxState.defectiveProductsCount = 0;
		_boxState.filling = FALSE;
		
		return TRUE;
	}
	else
	{
		sendEvent(EVT_ERR_FULL_QUEUE,&boxData); /* TODO : msgQSend ? */
		return FALSE;
	}
}

static void startBoxFilling ( )
{
	if (1/*TODOcarton présent*/)
	{
		_boxState.filling = TRUE;
		/* TODO relancer ProductStarvationHandler */
		/* TODO ouvrir le clapet */
	}
	else
	{
		sendEvent(EVT_ERR_BOX_STARVATION, NULL):
	}
}

static void stopBoxFilling ( )
{
	/* TODO fermer le clapet  */
	/* TODO arrêter ProductStarvationHandler */
	_boxState.filling = FALSE;
	/* TODO ajouter & détailler l'écriture dans BoxState dans la conception */
}

/*--------------------------------------------------*/
/* IT and alarm handlers */

/* TODO : vérifier la signature */
static int ProductStarvationHandler ( )
{
	stopBoxFilling();
	return 0;
}

/* TODO : vérifier la signature */
static int ProductInflowHandler ( )
{
	/* TODO : n'utiliser que stopBoxFilling(); , ne pas accéder directement au clapet */
	return 0;
}

/* TODO : vérifier la signature */
static int EmergencyStopHandler ( )
{
	stopBoxFilling();
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
		if (!_boxState.filling) /* TODO ajouter le ce test dans la conception */
		{
			if (_boxState.boxedProductsCount >=
					_settings->productsPerBox)
			{
				/* We have a full box. Let's try to send it to the printers */
				boxError = sendBox();
			}

			if (!boxError)
			{
				/* We can continue dropping products */
				
				if (_settings->applicationEndRequest)
				{
					/*TODO*/
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
	/*TODO*/

	return 0; /*TODO*/
}

