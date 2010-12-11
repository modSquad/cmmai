/* CIAI : Développement Multi-lots
* @author H4203
*
* This file contains simulated device access procedures, and a task
* managing the simulation.
*/

#include <stdio.h>
#include <taskLib.h>
#include <sysLib.h>
#include <time.h>
#include "devices_simulation.h"

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
... correct:     %5d\n\
... defective:   %5d\n\
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

/* Simulation config */
static int _brokenPrinterRate =	1;
static int _missingBoxRate =	1;
static int _defectRate =		1;

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
}

valveState_t valveState (valveName_t valveName)
/* returns TRUE if the valve is open and FALSE if not */
{
	return _valveState[valveName];
}

/* Interface for the sensors */
BOOL presenceDetected(presenceSensorName_t sensorName)
{
	if (_missingBoxRate != 0 && rand()%_missingBoxRate == 0)
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
	if (_defectRate != 0 && rand()%_defectRate == 0)
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
	if (_brokenPrinterRate != 0 && rand()%_brokenPrinterRate == 0)
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
	/* TODO ? */
}

/* Interface for the lights */
void setColor(color_t color)
{
	_lightColor = color;
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

int simulator (
		void (*simulationCallBack)(int),
		int updateDelay, int screenRefreshStep,
		int defectRate, int missingBoxRate, int brokenPrinterRate,
		)
{
	int updatesCount;

	_defectRate = defectRate;
	_missingBoxRate = missingBoxRate;
	_brokenPrinterRate = brokenPrinterRate;

	srand(time(NULL));

	for ( updatesCount = 0 ; ; ++updatesCount )
	{
		if (updatesCount%screenRefreshStep == 0)
		{
			refreshScreen();
		}

		simulationCallBack(updatesCount);

		taskDelay((int)(updateDelay*sysClkRateGet()));
	}
}


/* ------------------------------------------------------------
 * ACCESS FUNCTIONS
 * ------------------------------------------------------------ */

int defectiveProductCount ()
{
	return _defectiveProductCount;
}

int correctProductCount ()
{
	return _correctProductCount;
}

