/* CIAI : Développement Multi-lots
 * @author H4203
 */
#define SIMULATION

#include <stdio.h>
#include <stdlib.h>
#include <msgQLib.h>
#include <taskLib.h>
#include <sysLib.h>

#include "masterTask.h"
#include "boxingServer.h"
#include "networkInterface.h"
#include "networkListener.h"
#include "eventManager.h"
#include "boxManager.h"
#include "printManager.h"
#include "logsManager.h"
#include "eventToString.h"

#ifdef SIMULATION
#include "devices_simulation.h"
#include "simulatorControl.h"
#include "simulatorUpdater.h"
#define PRODUCT_GENERATION_DELAY	0.5	/* In seconds */
#endif

/* Application constants */
#define SERVER_PORT 4802
#define CLOCK_RATE  4000
/* Tasks priorities (relatives) */
#define BASE_PRIORITY (100)
#define NETWORK_LISTENER_PRIORITY (3)
#define EVENT_MANAGER_PRIORITY (2)
#define BOX_MANAGER_PRIORITY (0)
#define PRINT_MANAGER_PRIORITY (1)
#define LOGS_MANAGER_PRIORITY (2)
#ifdef SIMULATION
#define SIMULATOR_PRIORITY (-1)
#endif

/* Queues sizes */
#define MAX_EVENTS_QUEUE_SIZE	100
#define MAX_LOGS_QUEUE_SIZE		200

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
#ifdef SIMULATION
	int simulatorControlId;
	int simulatorUpdaterId;
#endif
	int networkListenerId;
	int eventManagerId;
	int boxManagerId;
	int printManagerId;
	int logsManagerId;
	
	/* Secure environment */
	setValveState(INLET_VALVE,CLOSED);
	setValveState(OUTLET_VALVE,CLOSED);

	/* Settings */
	sysClkRateSet(CLOCK_RATE);

	/* Creation of shared objects */
	endSync = semBCreate(0,SEM_EMPTY);
	boxHandlingRequest = semBCreate(0,SEM_EMPTY);
	settings = (settings_t*) malloc(sizeof(settings_t));
	settings->batchID = 0;
	settings->maxDefectiveProductsPerBox = 0;
	settings->productsPerBox = 0;
	settings->batchBoxesAsked = 0;
	settings->applicationEndRequest = FALSE;
	settings->batchBoxesCount = 0;
	boxesQueue = msgQCreate(MAX_BOXES_QUEUE_SIZE, sizeof(boxesQueueMsg_t), MSG_Q_FIFO);
	eventsQueue = msgQCreate(MAX_EVENTS_QUEUE_SIZE, sizeof(event_msg_t), MSG_Q_FIFO);
	logsEventQueue = msgQCreate(MAX_LOGS_QUEUE_SIZE, sizeof(event_msg_t), MSG_Q_FIFO);

	/*socket = getClientSocket(SERVER_PORT);*/

	/* Spawning tasks */
#ifdef SIMULATION
	initDevicesSimulation();
	simulatorControlId = taskSpawn("simulatorControlTask",
		BASE_PRIORITY+SIMULATOR_PRIORITY,
		0, DEFAULT_STACK_SIZE, simulatorControl,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	);
	simulatorUpdaterId = taskSpawn("simulatorUpdaterTask",
		BASE_PRIORITY+SIMULATOR_PRIORITY,
		0, DEFAULT_STACK_SIZE, simulatorUpdater,
		(int)(PRODUCT_GENERATION_DELAY*sysClkRateGet()),
		0, 0, 0, 0, 0, 0, 0, 0, 0
	);
#endif

	networkListenerId = taskSpawn("networkListenerTask",
		BASE_PRIORITY+NETWORK_LISTENER_PRIORITY,
		0, DEFAULT_STACK_SIZE, networkListener,
		socket, (int) eventsQueue, (int) settings,
		(int) boxHandlingRequest, 0, 0, 0, 0, 0, 0
	);
/*
	eventManagerId = taskSpawn("eventManagerTask",
		BASE_PRIORITY+EVENT_MANAGER_PRIORITY,
		0, DEFAULT_STACK_SIZE, eventManager,
		socket, (int) eventsQueue, (int) logsEventQueue,
		0, 0, 0, 0, 0, 0, 0
	);
*/
	boxManagerId = taskSpawn("boxManagerTask",
		BASE_PRIORITY+BOX_MANAGER_PRIORITY,
		0, DEFAULT_STACK_SIZE, boxManager,
		(int) boxesQueue, (int) eventsQueue, (int) settings,
		(int) boxHandlingRequest, 0, 0, 0, 0, 0, 0
	);

	printManagerId = taskSpawn("printManagerTask",
		BASE_PRIORITY+PRINT_MANAGER_PRIORITY,
		0, DEFAULT_STACK_SIZE, printManager,
		(int) boxesQueue, (int) eventsQueue,
		0, 0, 0, 0, 0, 0, 0, 0
	);

/*	logsManagerId = taskSpawn("logsManagerTask",
		BASE_PRIORITY+LOGS_MANAGER_PRIORITY,
		0, DEFAULT_STACK_SIZE, logsManager,
		(int) logsEventQueue, (int) endSync,
		0, 0, 0, 0, 0, 0, 0, 0
	);*/

	/* Waiting for synchronization semaphore */
	if(semTake(endSync, WAIT_FOREVER) == ERROR) {
		perror("Bad end of application syncronization - exiting anyway\n\n");
	}

	/* delete tasks */
/*	taskDelete(logsManagerId);*/
	taskDelete(printManagerId);
	taskDelete(boxManagerId);
/*	taskDelete(eventManagerId);*/
	taskDelete(networkListenerId);
#ifdef SIMULATION
	taskDelete(simulatorUpdaterId);
	taskDelete(simulatorControlId);
	cleanDevicesSimulation();
#endif

	/* destruct resources */
	/* TODO close(socket); */
	msgQDelete(logsEventQueue);
	msgQDelete(eventsQueue);
	msgQDelete(boxesQueue);
	free(settings);
	semDelete(boxHandlingRequest);
	semDelete(endSync);

	/* Secure environment */
	setValveState(INLET_VALVE,CLOSED);
	setValveState(OUTLET_VALVE,CLOSED);
	
	/* End of the application */
	return 0;
}
