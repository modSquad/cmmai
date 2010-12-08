/* CIAI : Développement Multi-lots
 * @author H4203
 */


#include <stdio.h>
#include <stdlib.h>
#include <msgQLib.h>
#include <taskLib.h>

#include "masterTask.h"
#include "boxingServer.h"
#include "networkInterface.h"
#include "networkListener.h"
#include "eventManager.h"
#include "boxManager.h"
#include "printManager.h"
#include "logsManager.h"
#include "eventToString.h"

/* Application constants */
#define SERVER_PORT 1001

/* Tasks priorities (relatives) */
#define BASE_PRIORITY (100)
#define NETWORK_LISTENER_PRIORITY (3)
#define EVENT_MANAGER_PRIORITY (2)
#define BOX_MANAGER_PRIORITY (0)
#define PRINT_MANAGER_PRIORITY (1)
#define LOGS_MANAGER_PRIORITY (2)

/* Queues sizes */
#define MAX_EVENTS_QUEUE_SIZE 	100
#define MAX_LOGS_QUEUE_SIZE 	200

/* Stack size */
#define DEFAULT_STACK_SIZE		10000	

int boxingServer()
{
	SEM_ID endSync;
	SEM_ID boxHandlingRequest;
	settings_t* settings;
	MSG_Q_ID boxesQueue;
	MSG_Q_ID eventsQueue;
	MSG_Q_ID logsEventQueue;
	int socket;
	int networkListenerId;
	int eventManagerId;
	int boxManagerId;
	int printManagerId;
	int logsManagerId;

	/* Creation of shared objects */
	endSync = semMCreate(SEM_Q_FIFO|SEM_DELETE_SAFE);
	boxHandlingRequest = semMCreate(SEM_Q_FIFO|SEM_DELETE_SAFE);
	settings = (settings_t*) malloc(sizeof(settings_t));
	boxesQueue = msgQCreate(MAX_BOXES_QUEUE_SIZE, sizeof(boxesQueueMsg_t), MSG_Q_FIFO);
	eventsQueue = msgQCreate(MAX_EVENTS_QUEUE_SIZE, sizeof(event_msg_t), MSG_Q_FIFO);
	logsEventQueue = msgQCreate(MAX_LOGS_QUEUE_SIZE, sizeof(event_msg_t), MSG_Q_FIFO);

	socket = getClientSocket(SERVER_PORT);

	/* Spawning tasks */
	networkListenerId = taskSpawn("networkListenerTask",
		BASE_PRIORITY+NETWORK_LISTENER_PRIORITY,
		0, DEFAULT_STACK_SIZE, networkListener,
		socket, (int) eventsQueue, (int) settings,
		(int) boxHandlingRequest, 0, 0, 0, 0, 0, 0
	);
	
	eventManagerId = taskSpawn("eventManagerTask",
		BASE_PRIORITY+EVENT_MANAGER_PRIORITY,
		0, DEFAULT_STACK_SIZE, eventManager,
		socket, (int) eventsQueue, (int) logsEventQueue,
		0, 0, 0, 0, 0, 0, 0
	);
		
	boxManagerId = taskSpawn("boxManagerTask",
		BASE_PRIORITY+BOX_MANAGER_PRIORITY,
		0, DEFAULT_STACK_SIZE, boxManager,
		(int) boxesQueue, (int) eventsQueue, (int) settings,
		(int) boxHandlingRequest, 0, 0, 0, 0, 0, 0
	);

	printManagerId = taskSpawn("printManagerTask",
		BASE_PRIORITY+PRINT_MANAGER_PRIORITY,
		0, DEFAULT_STACK_SIZE, printManager,
		(int) eventsQueue, (int) boxesQueue,
		0, 0, 0, 0, 0, 0, 0, 0
	);

	logsManagerId = taskSpawn("logsManagerTask",
		BASE_PRIORITY+LOGS_MANAGER_PRIORITY,
		0, DEFAULT_STACK_SIZE, logsManager,
		(int) logsEventQueue, (int) endSync,
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
	/* TODO : close(socket); */
	msgQDelete(logsEventQueue);
	msgQDelete(eventsQueue);
	msgQDelete(boxesQueue);
	free(settings);
	semDelete(boxHandlingRequest);
	semDelete(endSync);

	/* End of the application */
	return 0;
}
