/* CIAI : Développement Multi-lots
* @author H4203
*
* This file contains simulated device access procedures.
* 
*/


#include <stdio.h>
#include <taskLib.h>
#include <sysLib.h>
#include "devices_simulation.h"

#define CLOCK_RATE		4000
#define UPDATE_DELAY	0.05
#define SCREEN_REFRESH_STEP	10
#define NEWPAGE "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"

#define DEFECT_RATE			10	/* One in DEFECT_RATE products will be defective (randomly) */
#define MISSING_BOX_RATE	100	/* One in DEFECT_RATE boxes will be missing */
#define BROKEN_PRINTER_RATE	10	/* One in DEFECT_RATE print try will abort */


/* the valves states */
static valveState_t _valveState[] =
{
		FALSE, /* INLET_VALVE  */
		FALSE  /* OUTLET_VALVE */
};

/* the color of the lights */
static color_t _lightsColor = GREEN;

/* the printers states */
static BOOL _printerState[] =
{
		TRUE, /* PRINTR1 */
		TRUE  /* PRINTR2 */
};

static BOOL _productDefect = FALSE;
static BOOL _missingBox = FALSE;

/* Interface methods */
/* ----------------------------------------------------------------- */

/* Interface for the valves  - InletValve, OutletValve*/

void setValveState(valveName_t valveName, valveState_t valveState)
{
	_valveState[valveName] = valveState;
	printf("the valve state is set! \n");
}

valveState_t valveState (valveName_t valveName)
/* returns TRUE if the valve is opened and FALSE if not */
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
		_missingBox = TRUE;
	}
	else
	{
		_missingBox = FALSE;
	}
	
	return !_missingBox;
}

BOOL defectiveProduct(defectSensorName_t sensorName)
{
	printf( "detects whether the product that passed in front of the sensor is defected or not  \n");

	if (rand()%DEFECT_RATE == 0)
	{
		_productDefect = TRUE;
	}
	else
	{
		_productDefect = FALSE;
	}
	
	return _productDefect;
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
	lightsColor = color;
	printf( "the color is set  \n");
} 

color_t getColor()
{
	return lightsColor;
}

/*------------------------------------------------------------
  SIMULATOR
  ------------------------------------------------------------*/

void setPrinterState(printerName_t printerName, BOOL newPrinterState) 
{
	_printerState[printerName] = newPrinterState;
	printf( "the printer state is set  \n");
}

void refreshScreen ( )
{
	/* LIGHT */
	
	/* PRINTERS */
	
	/* VALVES */
	printStatus()
	
	/* SENSORS (last read) */
}

void simulate ( )
{
	
}

int devicesSimulator()
{
	int updatesCount;
	
	sysClkRateSet(CLOCK_RATE);
	
	printf("\n");
	for ( i = 0 ; ; ++i )
	{
		if (updatesCount >= SCREEN_REFRESH_STEP)
		{
			refreshScreen();
			updatesCount = 0;
		}
		
		simulate();
		
		taskDelay((int)(UPDATE_DELAY*sysClkRateGet()));
	}
}

