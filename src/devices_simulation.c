/* CIAI : DÃ©veloppement Multi-lots
* @author H4203
*
* This file contains simulated device access procedures.
* 
*/


#include <stdio.h>
#include <taskLib.h>
#include <sysLib.h>
#include <time.h>
#include "devices_simulation.h"

/* ------------------------------------------------------------
 * EXTERNAL FUNCTIONS (IT handlers to simulate)
 * ------------------------------------------------------------ */
 void EmergencyStopHandler ( );
 void ProductInflowHandler ( );

/* ------------------------------------------------------------
 * SIMULATION SETTINGS
 * ------------------------------------------------------------ */

#define CLOCK_RATE		4000
#define UPDATE_DELAY	0.05	/* In seconds */
#define SCREEN_REFRESH_STEP	20
	/* A screen refresh will occur every SCREEN_REFRESH_STEP updates */
#define PRODUCT_INFLOW_STEP 10
	/* A product inflow will occur every PRODUCT_INFLOW_STEP updates */

#define DEFECT_RATE			10	/* One in DEFECT_RATE products will be defective (randomly) */
#define MISSING_BOX_RATE	100	/* One in DEFECT_RATE boxes will be missing */
#define BROKEN_PRINTER_RATE	10	/* One in DEFECT_RATE print try will abort */


/* ------------------------------------------------------------
 * SCREEN OUTPUT
 * ------------------------------------------------------------ */

#define NEWPAGE "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"

#define SIMULATOR_PROMPT "\
Simulator v1.0\n\
\n\
\n\
============================================================\n\
Light:         %s\n\
============================================================\n\
Valve     | Inlet  | Outlet \n\
----------+--------+--------\n\
status    | %6s | %6s \n\
============================================================\n\
Printer # |    1    |    2    \n\
----------+---------+---------\n\
status    | %7s | %7s \n\
============================================================\n\
Last box was missing:        %s\n\
============================================================\n\
Last product was defective:  %s\n\
Product count: %5d\n\
... defective:   %5d\n\
... correct:     %5d\n\
============================================================\n\
"
 
const char* COLOR_LABEL[] =
{
	"RED",
	"GREEN",
	"ORANGE"
};

const char* VALVE_STATE_LABEL[] =
{
	"CLOSED",
	"OPEN"
};

const char* PRINTER_STATE_LABEL[] =
{
	"BROKEN",
	"OK"
};

const char* LAST_PRODUCT_DEFECT_LABEL[] =
{
	"NO",
	"YES"
};

const char* LAST_BOX_MISSING_LABEL[] =
{
	"NO",
	"YES"
};


/* ------------------------------------------------------------
 * STATIC VARIABLES
 * ------------------------------------------------------------ */

/* the light color */
static color_t _lightColor = GREEN;

/* the valves states */
static valveState_t _valveState[] =
{
		FALSE, /* INLET_VALVE  */
		FALSE  /* OUTLET_VALVE */
};

/* the printers states */
static BOOL _printerState[] =
{
		TRUE, /* PRINTR1 */
		TRUE  /* PRINTR2 */
};

static BOOL _lastProductDefect = FALSE;
static int  _productCount =				0;
static int  _correctProductCount =		0;
static int  _defectiveProductCount =	0;

static BOOL _lastBoxMissing = FALSE;

/* ------------------------------------------------------------
 * INTERFACE METHODS
 * ------------------------------------------------------------ */

/* Interface for the valves  - InletValve, OutletValve*/

void setValveState(valveName_t valveName, valveState_t valveState)
{
	_valveState[valveName] = valveState;
	printf("the valve state is set! \n");
}

valveState_t valveState (valveName_t valveName)
/* returns TRUE if the valve is open and FALSE if not */
{
	printf( "returns the state of the valve - opened or closed \n");
	return _valveState[valveName];
} 

/* Interface for the sensors */
BOOL presenceDetected(presenceSensorName_t sensorName)
{
	printf( "returns whether the sensor detected presence or not  \n");

	if (rand()%DEFECT_RATE == 0)
	{
		_lastBoxMissing = TRUE;
	}
	else
	{
		_lastBoxMissing = FALSE;
	}
	
	return !_lastBoxMissing;
}

BOOL defectiveProduct(defectSensorName_t sensorName)
{
	printf( "detects whether the product that passed in front of the sensor is defected or not  \n");

	if (rand()%DEFECT_RATE == 0)
	{
		_lastProductDefect = TRUE;
		++_correctProductCount;
	}
	else
	{
		_lastProductDefect = FALSE;
		++_defectiveProductCount;
	}
	
	return _lastProductDefect;
} 

/* Interface for the printers */

BOOL printerState(printerName_t printerName) 
{
	if (rand()%BROKEN_PRINTER_RATE == 0)
	{
		_printerState[printerName] = FALSE;
	}
	else
	{
		_printerState[printerName] = TRUE;
	}
} 

void print(printerName_t printerName, boxData_t boxData) 
{
	printf( "the box is being printed  \n");
} 

/* Interface for the lights */
void setColor(color_t color)
{
	_lightColor = color;
	printf( "the color is set  \n");
} 

color_t getColor()
{
	return _lightColor;
}


/* ------------------------------------------------------------
 * SIMULATOR
 * ------------------------------------------------------------ */

void refreshScreen ( )
{
	printf(NEWPAGE);

	printf(SIMULATOR_PROMPT,
			COLOR_LABEL[_lightColor],
			PRINTER_STATE_LABEL[_printerState[PRINTR1]],
			PRINTER_STATE_LABEL[_printerState[PRINTR2]],
			VALVE_STATE_LABEL[_valveState[INLET_VALVE]],
			VALVE_STATE_LABEL[_valveState[OUTLET_VALVE]],
			LAST_BOX_MISSING_LABEL[_lastBoxMissing],
			LAST_PRODUCT_DEFECT_LABEL[_lastProductDefect],
			_productCount, _correctProductCount, _defectiveProductCount
			);
}

void simulate (int updatesCount)
{
	if (updatesCount%PRODUCT_INFLOW_STEP == 0)
	{
		++_productCount;
		if (_valveState[INLET_VALVE] == OPEN)
		{
			ProductInflowHandler();
		}
	}
	
	/* TODO simuler l'arrêt d'urgence */
	/*EmergencyStopHandler();*/
}

int simulator()
{
	int updatesCount;
	
	srand(time(NULL));
	sysClkRateSet(CLOCK_RATE);
	
	printf("\n");
	for ( updatesCount = 0 ; ; ++updatesCount )
	{
		if (updatesCount%SCREEN_REFRESH_STEP == 0)
		{
			refreshScreen();
		}
		
		simulate(updatesCount);
		
		taskDelay((int)(UPDATE_DELAY*sysClkRateGet()));
	}
}

