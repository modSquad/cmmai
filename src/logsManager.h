/* CIAI : Développement Multi-lots
 * @author H4203
 *
 * Logs manager headers : manage write actions on the application log file.
 */

#ifndef LOGS_MANAGER_H
#define LOGS_MANAGER_H

#include "boxingServer.h"

const char* FILENAME = "log.log";

/**
 * Application bootstrap.
 * @param logsEventsQueue	Queue of events to be logged
 * @param endSync			End of application sync semaphore
 * @return int
 */
int logsManager(MSG_Q_ID logsEventsQueue, SEM_ID endSync);

#endif

