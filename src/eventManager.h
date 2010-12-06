/* CIAI : Développement Multi-lots
 * @author H4203
 *
 * Event Manager : task collecting and dispatching events happening in the
 * system.
 */

#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include "boxingServer.h"

/**
 * Event data
 */
typedef struct
{
	event_t eventType;
	boxData_t boxData;
} eventStruct_t;

/**
 * Bootstrap for the eventManager task.
 * @param socketInput	descriptor of the socket used to write data to client
 * @param eventsQueue	queue of events to be managed
 * @return int
 */
int eventManager(int socketInput, MSG_Q_ID eventsQueue);

/**
 * Send an event that will be processed by the event manager.
 *
 * @pre When the event does not concern a particular box,
 * <boxData> can be NULL (it will be ignored).
 * @pre When the event does concern a particular box,
 * <boxData> must be non-NULL (otherwise it will crash).
 */
void sendEvent (event_t eventType, const boxData_t *boxData);

#endif

