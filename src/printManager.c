#include <stdio.h> /* TODO : remove, for debug purpose */
#include <taskLib.h>
#include <msgQLib.h>
#include <wdLib.h>
#include <sysLib.h>
#include "printManager.h"
#include "devices.h"

#define PRINT_POLL_DELAY 1 /* In seconds */

static MSG_Q_ID		_boxesQueue = NULL;
static MSG_Q_ID		_eventsQueue = NULL;

static printerName_t printer1 = PRINTR1;
static printerName_t printer2 = PRINTR2;

/* Private functions */
/*--------------------------------------------------*/

static BOOL printBox(printerName_t printerName, boxData_t boxData)
{
	/* initialization */
	printerName_t _printerName = printerName;
	boxData_t _boxData = boxData;
	
	event_msg_t eventMsg; /* TODO - question */
	
	/* cheking printer */
	if ( printerState(_printerName) == TRUE )
		{
			/* print the box */
			print(_printerName, _boxData);
			eventMsg.event = EVT_BOX_PRINTED;
			msgQSend(_eventsQueue, (char*)&eventMsg, sizeof(eventMsg),
					WAIT_FOREVER, MSG_PRI_NORMAL);
			return TRUE;
		}
	else 
	{
		return FALSE;
	}
}

static void alternatePrinter()
{
	if(printer1 == PRINTR1)
	{
		printer1 = PRINTR2;
		printer2 = PRINTR1;
	}
	else
	{
		printer1 = PRINTR1;
		printer2 = PRINTR2;
	}
}

/* Bootstrap */
/*--------------------------------------------------*/

BOOL printManager(MSG_Q_ID boxesQueue, MSG_Q_ID eventsQueue)
{
	boxesQueueMsg_t currentBox;
	event_msg_t eventMsg;
	
	/* Initialization */
	_boxesQueue = boxesQueue;
	_eventsQueue = eventsQueue;
	
	
	
	for ( ; ; )
	{
		alternatePrinter();
		msgQReceive(_boxesQueue, (char*)&currentBox,
					sizeof(boxesQueueMsg_t),WAIT_FOREVER);
		
		if(currentBox.lastMessage == TRUE)
		{
			/* The message that the application is at its end is transmitted */
			eventMsg.event = EVT_APPLICATION_STOP;
			msgQSend(_eventsQueue, (char*)&eventMsg, sizeof(eventMsg),
					WAIT_FOREVER, MSG_PRI_NORMAL);
			taskSuspend(taskIdSelf());
		} 
		else
		{
			/* trying to print using PRINTER1 */
			if ( printBox(printer1, currentBox.boxData) == FALSE )
			{
				/* PRINTER1 doesn't work, we report the anomaly */
				eventMsg.event = EVT_ANOMALY_PRINTER1;
				msgQSend(_eventsQueue, (char*)&eventMsg, sizeof(eventMsg),
						WAIT_FOREVER, MSG_PRI_NORMAL);
				
				/* attempting to print using PRINTER2 */			
				if ( printBox(printer2, currentBox.boxData) == FALSE )
				{
					/* PRINTER2 doesn't work, we report the anomaly */
					eventMsg.event = EVT_ANOMALY_PRINTER2;
					msgQSend(_eventsQueue, (char*)&eventMsg, sizeof(eventMsg),
							WAIT_FOREVER, MSG_PRI_NORMAL);
							
					/* we wait for one printer to be fixed */
					while (
							!printBox(printer1, currentBox.boxData)
							&&
							!printBox(printer2, currentBox.boxData)
						)
					{
						alternatePrinter();
						taskDelay(PRINT_POLL_DELAY*sysClkRateGet());
					}
				}
			}
		}
	}

	return 0;
	
}
