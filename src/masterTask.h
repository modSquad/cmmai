/* CIAI : Développement Multi-lots
 * @author H4203
 *
 * Master task headers : manage lifecycle of objects and tasks.
 */

#ifndef MASTER_TASK_H
#define MASTER_TASK_H

#include "boxingServer.h"

/* Tasks priorities (relatives) */
#define BASE_PRIORITY (100)
#define NETWORK_LISTENER_PRIORITY (3)
#define EVENT_MANAGER_PRIORITY (2)
#define BOX_MANAGER_PRIORITY (0)
#define PRINT_MANAGER_PRIORITY (1)
#define LOGS_MANAGER_PRIORITY (2)

/**
 * Application bootstrap.
 * @return int
 */
int boxingServer();

#endif

