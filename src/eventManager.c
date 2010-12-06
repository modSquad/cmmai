#include "eventManager.h"
#include "msgQLib.h"

void sendEvent (event_t eventType, const boxData_t *boxData)
{
	eventStruct_t eventStruct;

	eventStruct.eventType = eventType;
	eventStruct.eventType = boxData;

	if((msgQSend(eventsQueue,eventStruct,sizeof(eventStruct_t), WAIT_FOREVER, MSG_PRI_NORMAL)) == ERROR)
	{
		// Send message fail
	}
}

void eventManager (int socketInput, MSG_Q_ID eventsQueue)
{
	eventStruct_t eventStruct;
	
	for(;;)
	{
		if( msgQReceive(eventsQueue, eventBuffer, sizeof(eventStruct_t), WAIT_FOREVER) == ERROR )
		{
			// Receive message fail
		}

		
		

		
	}
}
