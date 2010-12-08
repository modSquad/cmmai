/* CIAI : Développement Multi-lots
 * @author H4203
 *
 * Function to convert an event to a human-readable string.
 */

#ifndef EVENT_TO_STRING_H
#define EVENT_TO_STRING_H

#include <stddef.h>
#include "boxingServer.h"

#define MIN_EVENT_STRING_SIZE 512

/*
 * Convert an event to a human-readable string.
 *
 * The corresponding string will be stored in <eventString>
 * (empty string if no corresponding string exists).
 *
 * @pre When the event does not concern a particular box,
 * <boxData> can be NULL (it will be ignored).
 * @pre When the event does concern a particular box,
 * <boxData> must be non-NULL (otherwise the message will be incorrect).
 * @pre <eventString> must be non-NULL, allocated by user and
 * at least MIN_EVENT_STRING_SIZE long.
 */
void eventToString (boxingEvent_t eventType, const boxData_t* boxData,
		char* eventString);

#endif

