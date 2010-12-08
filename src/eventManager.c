#include <msgQLib.h>
#include <taskLib.h>

#include "boxingServer.h"
#include "eventManager.h"
#include "devices.h"
#include "eventToString.h"
#include "networkInterface.h"

int eventManager (int socketInput, MSG_Q_ID eventsQueue, MSG_Q_ID logsEventQueue)
{
	event_msg_t eventMsg;
	char logLine[MIN_EVENT_STRING_SIZE];
	
	for(;;)
	{
		if( msgQReceive(eventsQueue, (char*)&eventMsg, sizeof(event_msg_t),
				WAIT_FOREVER) == ERROR )
		{
			continue;
		}

		if(msgQSend(logsEventQueue, (char*)&eventMsg, sizeof(event_msg_t),
				WAIT_FOREVER, MSG_PRI_NORMAL ) == ERROR )
		{
			// send to log error
		}

		eventToString (eventMsg.event, &eventMsg.boxData, logLine);
		sendLog( socketInput, logLine, MIN_EVENT_STRING_SIZE);

		if( eventMsg.event != EVT_NONE )
		{
			setLight(eventMsg.event);
		}
		else
		{
			setLight(eventMsg.event);
			taskSuspend(taskIdSelf());
		}
		
	}
	
	return 0;
}
