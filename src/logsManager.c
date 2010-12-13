#include <semLib.h>
#include <msgQLib.h>
#include <stdio.h>
#include <ioLib.h>
#include <string.h>
#include "boxingServer.h"
#include "eventToString.h"
#include "logsManager.h"

const char* FILENAME = "log.log";

int logsManager(MSG_Q_ID logsEventsQueue, SEM_ID endSync)
{
	char logEntry[MIN_EVENT_STRING_BUFFER_SIZE];
	event_msg_t event_buffer;
	int log_fd = 0;
	
	log_fd = open(FILENAME, O_CREAT | O_TRUNC, 0777);
	if(log_fd == ERROR)
	{
		fprintf(stderr, "Cannot open log file.");
	}
	
	for(;;)
	{
		if(msgQReceive(logsEventsQueue, (char*)&event_buffer, sizeof(event_msg_t),WAIT_FOREVER) == ERROR)
		{
			fprintf(stderr, "Error while receiving message and about to write on disk");
			close(log_fd);
			return ERROR;
		}
		else
		{
			eventToString(event_buffer.event, &event_buffer.boxData, logEntry);
			write(log_fd, logEntry, strlen(logEntry));
			/* We must ensure that the data have been written to the
			 * disk : in case of critical error, this is the only
			 * way to know what happened in the system. */
			/* TODO : Find VxWorks equivalent for fflush */
			
		}	
	}
}
