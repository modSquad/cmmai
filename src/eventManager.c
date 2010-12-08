#include <msgQLib.h>
#include <taskLib.h>

#include "boxingServer.h"
#include "eventManager.h"
#include "devices.h"

void setLight(event_t event)
{

/* THIS METHOD HAS NO WAY TO WORK PROPERLY
 * because any of "Red" or "Orange" event could be set as resolved.
 */

	static lastPrimaryEvent = EVT_NONE;
	static lastSecondaryEvent = EVT_NONE; 
	
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

void eventManager (int socketInput, MSG_Q_ID eventsQueue, MSG_Q_ID logsEventQueue)
{
	event_msg_t eventMsg;
	char logLine[MIN_EVENT_STRING_SIZE];
	static event_t lastEvent;
	
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
