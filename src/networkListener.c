/* -------------------------------------------------------------------- */
/*                                                                      */
/*                    <networkInterface>.c  -  description                           */
/*                        -----------------------                       */
/*                                                                      */
/* -------------------------------------------------------------------- */
/*                                                                      */
/*    Realisation de la tache VxWorks <networkInterface>.c      */
/*                                                                      */
/* -------------------------------------------------------------------- */
/* ------------------------------------------------------------ INCLUDE */
/* ---------------------------------------------------- Include systme */
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

/* -------------------------------------------------- Include personnel */

/* -------------------------------------------------------------------- */
/*                                                                      */
/*                        PRIVE                                         */
/*                                                                      */
/* --------------------------------------------------------- Constantes */
/* -------------------------------------------------------------- Types */
/* -------------------------------------------------- Variables privees */
/*--------------------------------------------------- Fonctions privees */


static int handleRequest(const char* const buffer, int size, MSG_Q_ID eventsQueue,	settings_t* settings, SEM_ID boxHandlingRequest) {
	char* header = (char*)calloc(size, sizeof(char)); 
	int i  = 0;
	
	//while(buffer[i] != '\n' && i < size) header[i] = buffer[i++];
	sscanf (buffer,"%s ", header);
			
	if(strcmp(header, "CONFIG") == 0) {
		int opCode, threshold, ref, boxes, partPerBox;
		sscanf (buffer,"%*s %d %d %d %d %d", &opCode, &threshold, &ref, &boxes, &partPerBox );		
	
		settings->batchID = ref;
		settings->maxDefectiveProductsPerBox = threshold;
		settings->productsPerBox = partPerBox;
		settings->batchBoxesAsked = boxes;
	}
	
	if(strcmp(header, "LAUNCH") == 0) {
		semGive(boxHandlingRequest);
		
		event_msg_t msg; msg.event = EVT_APPLICATION_START;
		msgQSend(eventsQueue, (char*)&msg, sizeof(msg),NO_WAIT, MSG_PRI_NORMAL);
	}
	
	if(strcmp(header, "RESUME") == 0) {
		semGive(boxHandlingRequest);
		
		event_msg_t msg; msg.event = EVT_APPLICATION_START;
		msgQSend(eventsQueue, (char*)&msg, sizeof(msg),NO_WAIT, MSG_PRI_NORMAL);
	}
	
	if(strcmp(header, "STOP") == 0) {
		settings->applicationEndRequest = TRUE;
		
		event_msg_t msg; msg.event = EVT_APPLICATION_STOP;
		msgQSend(eventsQueue, (char*)&msg, sizeof(msg),NO_WAIT, MSG_PRI_NORMAL);
	}
	
	free(header);
	return 0;
}

/* -------------------------------------------------------------------- */
/*                                                                      */
/*                        PUBLIC                                        */
/*                                                                      */
/* ------------------------------------------------ Variables publiques */
/*------------------------------------------------- Fonctions publiques */
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
