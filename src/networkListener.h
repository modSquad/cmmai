/* CIAI : Développement Multi-lots
 * @author H4203
 *
 */

#ifndef NETWORK_LISTENER_H
#define NETWORK_LISTENER_H

#include <msgQLib.h>
#include <semLib.h>

#include "boxingServer.h"

/**
 * This task's role is to wait for message from client, and handle it. It currently handles several messages such as : LAUNCH, STOP, RESUME and CONFIG.
 * @param socketOutput : Socket's file descriptor
 * @param eventsQueue: Queue of events
 * @param settings : Pointer to a settings structure
 * @param boxHandlingRequest : Sync of networkListener and boxHandler
 * @return : NETWORK_SUCCESS if data were sent without error. NETWORK_ERROR otherwise.
 */
int networkListener(int socketOutput, MSG_Q_ID eventsQueue,
	settings_t* settings, SEM_ID boxHandlingRequest);

#endif

