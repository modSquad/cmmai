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
	char logMsg[MIN_EVENT_STRING_SIZE+4]; // sizeof("LOG\n[]\n\n")
	
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

		
		if(eventMsg.event == EVT_BOX_PROCESSED)
		{
			partAccepted(socketInput, event.boxData.boxedProducts);
			partRejected(socketInput, event.boxData.defectiveProducts);
		}

		if(eventMsg.event == EVT_ANOMALY_PRINTER1
		|| eventMsg.event == EVT_ANOMALY_PRINTER2 )
		{
			sendWarning(socketInput, eventMsg.event);
		}

		if(eventMsg.event == EVT_ERR_DEFECTIVE_TRESHOLD_REACHED
		|| eventMsg.event == EVT_ERR_FULL_QUEUE
		|| eventMsg.event == EVT_ERR_BOX_STARVATION
		|| eventMsg.event == EVT_ERR_PRODUCT_STARVATION )
		{
			sendError(socketInput, eventMsg.event);
		}


		eventToString (eventMsg.event, &eventMsg.boxData, logLine);
		sendLog(socketInput, logLine, MIN_EVENT_STRING_SIZE);

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
