/* CIAI : Développement Multi-lots
 * @author H4203
 */

#include "masterTask.h"

#include <stdlib.h>
#include <semMLib.h>
#include <msgQLib.h>
#include <taskLib.h>

#include "networkListener.h"
#include "eventManager.h"
#include "boxManager.h"
#include "printManager.h"
#include "logsManager.h"
#include "eventToString.h"

int boxingServer()
{
	SEM_ID endSync;
	SEM_ID boxHandlingRequest;
	settings_t* settings;
	MSG_Q_ID boxesQueue;
	MSG_Q_ID eventsQueue;
	MSG_Q_ID logsEventQueue;
	int socket;
	int networkListernerId;
	int eventManagerId;
	int boxManagerId;
	int printManagerId
	int logsManagerId;

	/* Creation of shared objects */
	endSync = semMCreate(SEM_Q_FIFO|SEM_DELETE_SAFE);
	boxHandlingRequest = semMCreate(SEM_Q_FIFO|SEM_DELETE_SAFE);
	settings = (settings_t*) malloc(sizeof(settings_t));
	boxesQueue = msgQCreate(MAX_BOXES_QUEUE_SIZE, sizeof(boxesQueueMsg_t), MSG_Q_FIFO);
	eventsQueue = msgQCreate(MAX_EVENTS_QUEUE_SIZE, sizeof(events_msg_t), MSG_Q_FIFO);
	logsEventQueue = msgQCreate(MAX_EVENTS_QUEUE_SIZE, sizeof(events_msg_t), MSG_Q_FIFO);
	/* TODO int	socket = init_connection(); */

	/* Spawning tasks */
	networkListenerId = taskSpawn("networkListenerTask",
		BASE_PRIORITY+NETWORK_LISTENER_PRIORITY,
		0, 1024, networkListener,
		socket, (MSG_Q_ID) eventsQueue, (settings_t*) settings,
		(SEM_ID) boxHandlingRequest, 0, 0, 0, 0, 0, 0
	);

	eventManagerId = taskSpawn("eventManagerTask",
		BASE_PRIORITY+EVENT_MANAGER_PRIORITY,
		0, 1024, eventManager,
		socket, (MSG_Q_ID) eventsQueue, (MSG_Q_ID) logsEventQueue,
		0, 0, 0, 0, 0, 0, 0
	);
		
	boxManagerId = taskSpawn("boxManagerTask",
		BASE_PRIORITY+BOX_MANAGER_PRIORITY,
		0, 1024, boxManager,
		(MSG_Q_ID) boxesQueue, (MSG_Q_ID) eventsQueue, (settings_t*) settings,
		(SEM_ID) boxHandlingRequest, 0, 0, 0, 0, 0, 0
	);

	printManagerId = taskSpawn("printManagerTask",
		BASE_PRIORITY+PRINT_MANAGER_PRIORITY,
		0, 1024, printManager,
		(MSG_Q_ID) eventsQueue, (MSG_Q_ID) boxesQueue,
		0, 0, 0, 0, 0, 0, 0, 0
	);

	logsManagerId = taskSpawn("logsManagerTask",
		BASE_PRIORITY+LOGS_MANAGER_PRIORITY,
		0, 1024, logsManager,
		(MSG_Q_ID) logsEventQueue, (SEM_ID) endSync,
		0, 0, 0, 0, 0, 0, 0, 0
	);

	/* Waiting for synchronization semaphore */
	if(semTake(endSync, WAIT_FOREVER) == ERROR) {
		perror("Bad end of application syncronization - exiting anyway\n\n");
	}

	/* delete tasks */
	taskDelete(logsManagerId);
	taskDelete(printManagerId);
	taskDelete(boxManagerId);
	taskDelete(eventManagerId);
	taskDelete(networkListenerId);

	/* destruct resources */
	close(socket);
	msgQDelete(logsEventQueue);
	msgQDelete(eventsQueue);
	msgQDelete(boxesQueue);
	free(settings);
	semDelete(boxHandlingRequest);
	semDelete(endSync);

	/* End of the application */
	return 0;
}
