/* CIAI : Développement Multi-lots
 * @author H4203
 *
 * printManager task : manages the box printing
 *
 */

#ifndef PRINT_MANAGER_H
#define PRINT_MANAGER_H

#include "boxingServer.h"


/**
 * Bootstrap for printManagerTask.
 * @param boxesQueue			queue of boxes to be labelled by printers
 * @param eventsQueue			queue of events to be logged or given to client
 * @return int
 */
int printManager(MSG_Q_ID boxesQueue, MSG_Q_ID eventsQueue);

#endif

