/* CIAI : Développement Multi-lots
 * @author H4203
 *
 * Network listeners dispatch into the application message received through the
 * network.
 */

#ifndef NETWORK_LISTENER_H
#define NETWORK_LISTENER_H

#include <msgQLib.h>
#include <semLib.h>

#include "boxingServer.h"

/**
 * networkListener is the bootstrap of the self-named task.
 * @param socketOutput			file descriptor of the socket
 * @param eventsQueue			Queue of events
 * @param settings				Settings structure
 * @param boxHandlingRequest	Sync of networkListener and boxHandler
 * @return int
 */
int networkListener(int socketOutput, MSG_Q_ID eventsQueue,
	settings_t* settings, SEM_ID boxHandlingRequest);

#endif

