/* CIAI : Développement Multi-lots
 * @author H4203
 *
 * boxManager task : manages the box detection, its filling and send a full
 * box to printing.
 */

#ifndef BOX_MANAGER_H
#define BOX_MANAGER_H

#include "boxingServer.h"

/**
 * Bootstrap for boxManagerTask.
 * @param productStarvation		Id of the watchdog looking for product starvation
 * @param boxesQueue			queue of boxes to be labelled by printers
 * @param eventsQueue			queue of events to be logged or given to client
 * @param settings				Structure of settings
 * @param boxState				Structure of currently managed box by boxManager
 * @param boxHandlingRequest	semaphore of activation of the box handling
 * @return int
 */
int boxManager(WDOG_ID productStarvation, MSG_Q_ID boxesQueue, MSG_Q_ID eventsQueue, settings_t settings, boxstate_t boxState, SEM_ID boxHandlingRequest);

#endif

