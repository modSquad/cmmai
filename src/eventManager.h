/* CIAI : Développement Multi-lots
 * @author H4203
 *
 * Event Manager : task collecting and dispatching events happening in the
 * system.
 */

#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <msgQLib.h>

/**
 * Bootstrap for the eventManager task.
 * @param socketInput		descriptor of the socket used to write data to client
 * @param eventsQueue		queue of events to be managed
 * @param logsEventQueue	queue of messages to be logged
 * @return int
 */
int eventManager(int socketInput, MSG_Q_ID eventsQueue, MSG_Q_ID logsEventQueue);

#endif

