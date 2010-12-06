/* CIAI : Développement Multi-lots
 * @author H4203
 *
 * Task managing the printing of label on boxes.
 */

#ifndef PRINT_MANAGER_H
#define PRINT_MANAGER_H

#include "boxingServer.h"

/**
 * Bootstrap for printManager task.
 * @param eventsQueue	Queue of events
 * @param boxesQueue	Queue of boxes to be labelled
 * @return int
 */
int printManager(MSG_Q_ID eventsQueue, MSG_Q_ID boxesQueue);

#endif

