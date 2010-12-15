#include <stdio.h>
#include "eventToString.h"

#define BOX_DATA_STRING_SIZE 100
static const char BOX_DATA_FORMAT_PRINTED[] =
	"[batch #%d / box #%d, %d products boxed / %d defective products, printed on %s]";
static const char BOX_DATA_FORMAT_NOT_PRINTED[] =
	"[batch #%d / box #%d, %d products boxed / %d defective products]";

static const char* PRINTER_LABEL[] =
{
		"No printer", /* NO_PRINTER */
		"Printer #1", /* PRINTR1 */
		"Printer #2"  /* PRINTR2 */
};

static const char MSG_APPLICATION_START[] =
	"Application start requested.";
static const char MSG_APPLICATION_STOP[] =
	"Application end requested.";
static const char MSG_END_FILLING[] =
	"End of filling on box %s.";
static const char MSG_CLOSE_APPLICATION[] =
	"End. Good bye!";
static const char MSG_BOX_PROCESSED[] =
	"Box %s processed.";
static const char MSG_BOX_PRINTED[] =
	"Box %s printed."; 
static const char MSG_ANOMALY_PRINTER1[] =
	"ANOMALY: Printer #1 broken while trying to print %s.";
static const char MSG_ANOMALY_PRINTER2[] =
	"ANOMALY: Printer #2 broken while trying to print %s.";
static const char MSG_EMERGENCY_STOP[] =
	"ERROR: Emergency stop.";
static const char MSG_ERR_DEFECTIVE_TRESHOLD_REACHED[] =
	"ERROR: Defective treshold reached on box %s.";
static const char MSG_ERR_FULL_QUEUE[] =
	"ERROR: Full queue while trying to add box %s.";
static const char MSG_ERR_BOX_STARVATION[] =
	"ERROR: No box available.";
static const char MSG_ERR_PRODUCT_STARVATION[] =
	"ERROR: Product starvation when trying to fill the box %s.";

void eventToString (boxingEvent_t eventType, const boxData_t* boxData,
		char* eventString)
{
	char boxDataString[BOX_DATA_STRING_SIZE];
	boxDataString[0] = '\0';
	eventString[0] = '\0';
	
	if (boxData != NULL)
	{
		if (boxData->printer == NO_PRINTER)
			sprintf(boxDataString, BOX_DATA_FORMAT_NOT_PRINTED,
					boxData->batchID,
					boxData->boxID,
					boxData->boxedProducts,
					boxData->defectiveProducts
				   );
		else
			sprintf(boxDataString, BOX_DATA_FORMAT_PRINTED,
					boxData->batchID,
					boxData->boxID,
					boxData->boxedProducts,
					boxData->defectiveProducts,
					PRINTER_LABEL[boxData->printer]
				   );
	}

	switch (eventType)
	{
		case EVT_APPLICATION_START :
			sprintf(eventString, MSG_APPLICATION_START,
					boxDataString);
			break;
		case EVT_APPLICATION_STOP :
			sprintf(eventString, MSG_APPLICATION_STOP,
					boxDataString);
			break;
		case EVT_END_FILLING :
			sprintf(eventString, MSG_END_FILLING,
					boxDataString);
			break;
		case EVT_CLOSE_APPLICATION :
			sprintf(eventString, MSG_CLOSE_APPLICATION,
					boxDataString);
			break;
		case EVT_BOX_PROCESSED :
			sprintf(eventString, MSG_BOX_PROCESSED,
					boxDataString);
			break;
		case EVT_BOX_PRINTED :
			sprintf(eventString, MSG_BOX_PRINTED,
					boxDataString);
			break;
		case EVT_ANOMALY_PRINTER1 :
			sprintf(eventString, MSG_ANOMALY_PRINTER1,
					boxDataString);
			break;
		case EVT_ANOMALY_PRINTER2 :
			sprintf(eventString, MSG_ANOMALY_PRINTER2,
					boxDataString);
			break;
		case EVT_EMERGENCY_STOP :
			sprintf(eventString, MSG_EMERGENCY_STOP,
					boxDataString);
			break;
		case EVT_ERR_DEFECTIVE_TRESHOLD_REACHED :
			sprintf(eventString, MSG_ERR_DEFECTIVE_TRESHOLD_REACHED,
					boxDataString);
			break;
		case EVT_ERR_FULL_QUEUE :
			sprintf(eventString, MSG_ERR_FULL_QUEUE,
					boxDataString);
			break;
		case EVT_ERR_BOX_STARVATION :
			sprintf(eventString, MSG_ERR_BOX_STARVATION,
					boxDataString);
			break;
		case EVT_ERR_PRODUCT_STARVATION :
			sprintf(eventString, MSG_ERR_PRODUCT_STARVATION,
					boxDataString);
			break;
		default :
			fprintf(stderr, "RUNTIME ERROR: Unhandled event: %d\n", eventType);
			break;
	}
	
	//sprintf(eventString, "%s : %s", eventString, ctime());
}
