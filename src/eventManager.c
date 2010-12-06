#include "eventManager.h"
#include "msgQLib.h"

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
