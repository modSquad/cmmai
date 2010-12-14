#include <stdio.h>
#include <msgQLib.h>
#include <taskLib.h>

#include "boxingServer.h"
#include "eventManager.h"
#include "devices.h"
#include "eventToString.h"
#include "networkInterface.h"

typedef enum
{
    EVT_LVL_NORMAL = 0,
    EVT_LVL_ANOMALY = 1,
    EVT_LVL_ERROR = 2
} badEventLevel_t;

typedef struct
{
    boxingEvent_t event;
    badEventLevel_t level;
    BOOL active;
} badEventStatus_t;

/*
 * This is the table allowing us to remember what "bad" events
 * (anomalies and errors) occured and are still valid.
 * This is used in order to set the light color.
 */
#define EVENT_STATUS_SIZE 7
static badEventStatus_t EVENT_STATUS[] =
{
    /* Anomalies */
    {EVT_ANOMALY_PRINTER1,	EVT_LVL_ANOMALY, FALSE},
    {EVT_ANOMALY_PRINTER2,	EVT_LVL_ANOMALY, FALSE},

    /* Errors */
    {EVT_EMERGENCY_STOP,					EVT_LVL_ERROR, FALSE},
    {EVT_ERR_DEFECTIVE_TRESHOLD_REACHED,	EVT_LVL_ERROR, FALSE},
    {EVT_ERR_FULL_QUEUE,					EVT_LVL_ERROR, FALSE},
    {EVT_ERR_BOX_STARVATION,				EVT_LVL_ERROR, FALSE},
    {EVT_ERR_PRODUCT_STARVATION,			EVT_LVL_ERROR, FALSE}
};

static void setEventStatus (boxingEvent_t event, BOOL status)
{
    int eventIndex;

    /* We seek the event to update */
    for ( eventIndex = 0 ;
	    eventIndex < EVENT_STATUS_SIZE
	    && EVENT_STATUS[eventIndex].event != event ;
	    ++eventIndex )
    {
	/* Empty block */
    }

    if (eventIndex < EVENT_STATUS_SIZE)
    {
	/* We found the event */
	EVENT_STATUS[eventIndex].active = status;
    }
}

/*
 * Update the light color according to the last received event <event>,
 * with box data <boxData>
 */
static void updateLightColor (boxingEvent_t event, boxData_t *boxData)
{
    int eventIndex;
    badEventLevel_t maxEventLevel;

    switch (event)
    {
	case EVT_ANOMALY_PRINTER1 :
	case EVT_ANOMALY_PRINTER2 :
	case EVT_EMERGENCY_STOP :
	case EVT_ERR_DEFECTIVE_TRESHOLD_REACHED :
	case EVT_ERR_FULL_QUEUE :
	case EVT_ERR_BOX_STARVATION :
	case EVT_ERR_PRODUCT_STARVATION :
	    setEventStatus(event, TRUE);
	    break;

	case EVT_APPLICATION_START :
	    /* User handled an error ; we can clear all
	     * error events.
	     */
	    setEventStatus(EVT_EMERGENCY_STOP,FALSE);
	    setEventStatus(EVT_ERR_DEFECTIVE_TRESHOLD_REACHED,FALSE);
	    setEventStatus(EVT_ERR_FULL_QUEUE,FALSE);
	    setEventStatus(EVT_ERR_BOX_STARVATION,FALSE);
	    setEventStatus(EVT_ERR_PRODUCT_STARVATION,FALSE);
	    break;

	case EVT_BOX_PRINTED :
	    if (boxData == NULL)
		fprintf(stderr,"Error: Null pointer to printed box in 'box printed' event.\n");
	    else if (boxData->printer == PRINTR1)
		setEventStatus(EVT_ANOMALY_PRINTER1, FALSE);
	    else if (boxData->printer == PRINTR2)
		setEventStatus(EVT_ANOMALY_PRINTER2, FALSE);
	    else
		fprintf(stderr,"Error: Unknown printer in 'box printed' event.\n");
	    break;

	default :
	    break;
    }

    /* We seek the maximum "badness" level of all active events */
    for ( eventIndex = 0, maxEventLevel = EVT_LVL_NORMAL ;
	    eventIndex < EVENT_STATUS_SIZE ;
	    ++eventIndex )
    {
	if (EVENT_STATUS[eventIndex].active
		&& EVENT_STATUS[eventIndex].level > maxEventLevel)
	{
	    maxEventLevel = EVENT_STATUS[eventIndex].level;
	}
    }

    switch(maxEventLevel)
    {
	case EVT_LVL_NORMAL :
	    setColor(GREEN);
	    break;
	case EVT_LVL_ANOMALY :
	    setColor(ORANGE);
	    break;
	case EVT_LVL_ERROR :
	    setColor(RED);
	    break;
    }
}

int eventManager (int socketInput, MSG_Q_ID eventsQueue, MSG_Q_ID logsEventQueue)
{
    BOOL endOfTask = FALSE;
    event_msg_t eventMsg;
    char logLine[MIN_EVENT_STRING_BUFFER_SIZE];

    while (!endOfTask)
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

	switch(eventMsg.event)
	{
	    case EVT_CLOSE_APPLICATION :
		endOfTask = TRUE;
		/* We don't need to propagate the message, it is done above */
		break;

	    case EVT_BOX_PROCESSED :
		partAccepted(socketInput, eventMsg.boxData.boxedProducts);
		partRejected(socketInput, eventMsg.boxData.defectiveProducts);
		break;

	    case EVT_ANOMALY_PRINTER1 :
	    case EVT_ANOMALY_PRINTER2 :
		sendWarning(socketInput, eventMsg.event);
		break;

	    case EVT_EMERGENCY_STOP :
	    case EVT_ERR_DEFECTIVE_TRESHOLD_REACHED :
	    case EVT_ERR_FULL_QUEUE :
	    case EVT_ERR_BOX_STARVATION :
	    case EVT_ERR_PRODUCT_STARVATION :
		sendError(socketInput, eventMsg.event);
		break;
	    default :
		break;
	}

	eventToString (eventMsg.event, &eventMsg.boxData, logLine);
	sendLog(socketInput, logLine, MIN_EVENT_STRING_BUFFER_SIZE);

	updateLightColor(eventMsg.event, &eventMsg.boxData);
    }

    return 0;
}
