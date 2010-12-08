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
 * @param [in] socketOutput : Socket's file descriptor
 * @param [in] eventsQueue : Event mailbox identifier.
 * @param [in] settings : Pointer to box configuration.
 * @param [in] boxHandlingRequest : Mutex identifier for stop or restart all tasks
 * @return : NETWORK_SUCCESS if data were sent without error. NETWORK_ERROR otherwise.
 */
int networkListener(int socketOutput, MSG_Q_ID eventsQueue,
	settings_t* settings, SEM_ID boxHandlingRequest);

#endif

