#include <stdio.h>
#include "eventToString.h"

static const size_t BOX_DATA_STRING_SIZE = 100;
static const char BOX_DATA_FORMAT[] =
	"[batch #%d / box #%d, %d products boxed / %d defective products]";

static const char MSG_ERR_BOX_STARVATION[] =
	"ERROR: No box available.";
static const char MSG_ERR_PRODUCT_STARVATION[] =
	"ERROR: Product starvation when trying to fill the following box : %s.";

void eventToString (event_t eventType, const boxData_t* boxData,
		char* eventString)
{
	char boxDataString[BOX_DATA_STRING_SIZE];
	boxDataString[0] = '\0';
	eventString[0] = '\0';

	if (boxData != NULL)
	{
		sprintf(boxDataString, BOX_DATA_FORMAT,
				boxData->batchID,
				boxData->boxID,
				boxData->boxedProducts,
				boxData->defectiveProducts
			   );
	}

	switch (eventType)
	{
		/* TODO */
		case EVT_ERR_BOX_STARVATION :
			sprintf(eventString, MSG_ERR_BOX_STARVATION,
					boxDataString);
			break;
		case EVT_ERR_PRODUCT_STARVATION :
			sprintf(eventString, MSG_ERR_PRODUCT_STARVATION,
					boxDataString);
			break;
		default :
			break;
	}
}

