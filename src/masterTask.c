/* CIAI : Développement Multi-lots
 * @author H4203
 */

#include "masterTask.h"

#include <stdlib.h>
#include <msgQLib.h>
#include <semLib.h>

int boxingServer()
{
	SEM_ID endSync;
	SEM_ID boxHandlingRequest;
	settings_t* settings;
	MSG_Q_ID boxesQueue;
	MSG_Q_ID eventsQueue;
	int socket;

	/* Creation of shared objects */
	endSync = semMCreate(SEM_Q_FIFO|SEM_DELETE_SAFE);
	boxHandlingRequest = semMCreate(SEM_Q_FIFO|SEM_DELETE_SAFE);
	settings = (settings_t*) malloc(sizeof(settings_t));
	boxesQueue = msgQCreate(MAX_BOXES_QUEUE_SIZE, sizeof(boxesQueueMsg_t), MSG_Q_FIFO);
	eventsQueue = msgQCreate(MAX_EVENTS_QUEUE_SIZE, sizeof(events_msg_t), MSG_Q_FIFO);
	
	/* Spawning tasks */


	/* Waiting for  synchronization semaphore */
	

	/* End of the application */
	return 0;
}
