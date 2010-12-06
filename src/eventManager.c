#include "eventManager.h"
#include "msgQLib.h"

void sendEvent (event_t eventType, const boxData_t *boxData)
{
	/* TODO */
}

void eventManager ()
{
	char eventBuffer[MAX_EVENT_LENGTH]
	

	for(;;)
	{
		if( msgQReceive(eventsQueue, eventBuffer, MAX_EVENT_LENGTH, WAIT_FOREVER) == ERROR )
		{
			// Receive message fail
		};


		if((msgQSend(mesgQueueId,message,MAX_EVENT_LENGTH, WAIT_FOREVER, MSG_PRI_NORMAL)) == ERROR)
		
	}
}
