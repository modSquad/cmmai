#include <msgQLib.h>
#include <taskLib.h>

#include "boxingServer.h"
#include "eventManager.h"
#include "devices.h"
#include "eventToString.h"
#include "networkInterface.h"

 /* Compute and set the color corresponding to an event */
void setLight(boxingEvent_t event)
{
/* THIS METHOD HAS NO WAY TO WORK PROPERLY
 * because any of "Red" or "Orange" event could be set as resolved.
 */

	static boxingEvent_t lastPrimaryEvent = EVT_NONE;
	static boxingEvent_t lastSecondaryEvent = EVT_NONE; 
	
	if(event == EVT_NONE)
	{
		setColor(GREEN);
	}

	//Red :
	if(event == EVT_EMERGENCY_STOP
	|| event == EVT_ERR_FULL_QUEUE
	|| event == EVT_ERR_PRODUCT_STARVATION
	|| event == EVT_ERR_BOX_STARVATION
	|| event == EVT_ERR_DEFECTIVE_TRESHOLD_REACHED )
	{
		setColor(RED);
		lastPrimaryEvent = event;
	}

	//Orange :
	if(event == EVT_ANOMALY_PRINTER1
	|| event == EVT_ANOMALY_PRINTER2 )
	{
		if(lastPrimaryEvent == EVT_NONE)
		{
			setColor(ORANGE);
		}
		else
		{
			lastSecondaryEvent = event;
		}
	}

	//Green :
	if(event == EVT_END_FILLING
	|| event == EVT_CLOSE_APPLICATION
	|| event == EVT_BOX_PROCESSED
	|| event == EVT_BOX_PRINTED )
	{
		if(lastPrimaryEvent == EVT_NONE)
		{
			if(lastSecondaryEvent == EVT_NONE)
			{
				setColor(GREEN);
			}
			else
			{
				setColor(ORANGE);
			}
		}
	}
}


int eventManager (int socketInput, MSG_Q_ID eventsQueue, MSG_Q_ID logsEventQueue)
{
	event_msg_t eventMsg;
	char logLine[MIN_EVENT_STRING_BUFFER_SIZE];

	
	for(;;)
	{
		if( msgQReceive(eventsQueue, (char*)&eventMsg, sizeof(event_msg_t),
				WAIT_FOREVER) == ERROR )
		{
			continue;
		}

		/* Send the message to the task that handle the file on disk. */
		msgQSend(logsEventQueue, (char*)&eventMsg, sizeof(event_msg_t),
				WAIT_FOREVER, MSG_PRI_NORMAL );
		

		
		if(eventMsg.event == EVT_BOX_PROCESSED)
		{
			partAccepted(socketInput, eventMsg.boxData.boxedProducts);
			partRejected(socketInput, eventMsg.boxData.defectiveProducts);
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
		sendLog(socketInput, logLine, MIN_EVENT_STRING_BUFFER_SIZE);


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
