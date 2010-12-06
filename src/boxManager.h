/* CIAI : Développement Multi-lots
 * @author H4203
 *
 * boxManager task : manages the box detection, its filling and send a full
 * box to printing.
 */

#ifndef BOX_MANAGER_H
#define BOX_MANAGER_H

#include <msgQLib.h>
#include <semLib.h>
#include "boxingServer.h"

/**
 * Currently filling box data
 */
typedef struct
{
	boxID_t boxID;
	productsCount_t boxedProductsCount;
	productsCount_t defectiveProductsCount;
	BOOL filling; /* Are we currently filling the box ? */
	/* TODO */
} boxState_t;

/**
 * Bootstrap for boxManagerTask.
 * @param boxesQueue			queue of boxes to be labelled by printers
 * @param eventsQueue			queue of events to be logged or given to client
 * @param settings				Structure of settings
 * @param boxHandlingRequest	semaphore of activation of the box handling
 * @return int
 */
int boxManager(MSG_Q_ID boxesQueue, MSG_Q_ID eventsQueue,
		settings_t* settings, SEM_ID boxHandlingRequest);

#endif

