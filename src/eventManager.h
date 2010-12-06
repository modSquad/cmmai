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
 * Send an event that will be processed by the event manager.
 *
 * @pre When the event does not concern a particular box,
 * <boxData> can be NULL (it will be ignored).
 * @pre When the event does concern a particular box,
 * <boxData> must be non-NULL (otherwise it will crash).
 */
void sendEvent (event_t eventType, const boxData_t *boxData);

void eventManager ();

#endif

