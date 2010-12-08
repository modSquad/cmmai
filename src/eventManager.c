#include "eventManager.h"
#include "msgQLib.h"
#include "taskLib.h"

void eventManager (int socketInput, MSG_Q_ID eventsQueue, MSG_Q_ID logsEventQueue)
{
	event_msg_t eventMsg;
	char[MIN_EVENT_STRING_SIZE] logLine;
	
	for(;;)
	{
		if( msgQReceive(eventsQueue, eventMsg, sizeof(event_msg_t), WAIT_FOREVER) == ERROR )
		{
			continue;
		}

		if(msgQSend(logsEventQueue, eventMsg, sizeof(event_msg_t), WAIT_FOREVER ) == ERROR )
		{
			// send to log error
		}

		eventToString (eventMsg.event, eventMsg.boxData, logLine);
		send( socketInput, logLine, MIN_EVENT_STRING_SIZE, 0);

		if( eventMsg.event != EVT_NONE )
		{
			setLight(eventMsg.event);
			lastEvent = eventMsg.event;
		}
		else
		{
			setLight(eventMsg.event);
			taskSuspend(taskIdSelf());
		}
		
	}
}
