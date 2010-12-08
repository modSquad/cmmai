/* CIAI : Développement Multi-lots
 * @author H4203
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <sockLib.h>
#include <taskLib.h>
#include <inetLib.h>
#include <fioLib.h>
#include <msgQLib.h>
#include <semLib.h>

#include "eventToString.h"
#include "networkInterface.h"


/* PRIVATE 
 * handleClient request such as : CONFIG - Write new configuration to shared memory block.
 *                                LAUNCH - Launch the process.
 *                                RESUME - Restart all task after an emergency stop.
 *                                STOP - Stop the process and initiate the application end.
 * @param [in] buffer : Datas read out of the client socket.
 * @param [in] size : Buffer size.
 * @param [int] eventsQueue : Event mailbox identifier.
 * @param [in] settings : Pointer to box configuration.
 * @param [in] boxHandlingRequest : Mutex identifier for stop or restart all tasks
 * @return : NETWORK_SUCCESS if data were sent without error. NETWORK_ERROR otherwise.
 */
static int handleRequest(const char* const buffer, int size, MSG_Q_ID eventsQueue,	settings_t* settings, SEM_ID boxHandlingRequest) {
	char* header = (char*)calloc(size, sizeof(char)); 
	int i  = 0;

	sscanf (buffer,"%s ", header); /* Fetch the request header */

	if(strcmp(header, "CONFIG") == 0) {
		int opCode, threshold, ref, boxes, partPerBox;
		sscanf (buffer,"%*s %d %d %d %d %d", &opCode, &threshold, &ref, &boxes, &partPerBox );		

		settings->batchID = ref;
		settings->maxDefectiveProductsPerBox = threshold;
		settings->productsPerBox = partPerBox;
		settings->batchBoxesAsked = boxes;
	}

	if(strcmp(header, "LAUNCH") == 0) {
		event_msg_t msg; 
		semGive(boxHandlingRequest); /* Allow other tasks to restart */

		msg.event = EVT_APPLICATION_START;
		msgQSend(eventsQueue, (char*)&msg, sizeof(msg),NO_WAIT, MSG_PRI_NORMAL);
	}

	if(strcmp(header, "RESUME") == 0) {
		event_msg_t msg; 
		semGive(boxHandlingRequest); /* Allow other tasks to restart */

		msg.event = EVT_APPLICATION_START;
		msgQSend(eventsQueue, (char*)&msg, sizeof(msg),NO_WAIT, MSG_PRI_NORMAL);
	}

	if(strcmp(header, "STOP") == 0) {
		event_msg_t msg; 
		settings->applicationEndRequest = TRUE;

		msg.event = EVT_APPLICATION_STOP;
		msgQSend(eventsQueue, (char*)&msg, sizeof(msg),NO_WAIT, MSG_PRI_NORMAL);
	}

	free(header);
	return 0;
}

int networkListener(int socketOutput, MSG_Q_ID eventsQueue,	settings_t* settings, SEM_ID boxHandlingRequest) {
	char* clientRequest = (char*)calloc(MIN_EVENT_STRING_SIZE, sizeof(char));
	int readBytes = -1;

	while ((readBytes = read (socketOutput, clientRequest, MIN_EVENT_STRING_SIZE)) > 0)
	{
		handleRequest(clientRequest, readBytes, eventsQueue, settings,  boxHandlingRequest);		
	}

	if (readBytes == ERROR){ 
		close(socketOutput);
		return NETWORK_ERROR;
	}

	/* Disconnection */
	close(socketOutput);
	return NETWORK_SUCCESS;
}
