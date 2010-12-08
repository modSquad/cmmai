/* CIAI : Développement Multi-lots
* @author H4203
*
* This file contains simulation procedures of the devices used by our application.
* 
*/

#include <stdio.h>
#include "devices.h"

/* the state of the Inlet valve */
static BOOL inletValveState = FALSE;

/* the state of the Outlet valve */
static BOOL outletValveState = FALSE;

/* the color of the lights */
static color_t lightsColor = GREEN;

/* the state of the printers */
static BOOL printer1State = TRUE;
static BOOL printer2State = TRUE;

/* Interface methods */
/* ----------------------------------------------------------------- */

/* Interface for the valves  - InletValve, OutletValve*/

void setValveState(valveName_t valveName, BOOL valveState);
{
	if(valveName == INLET_VALVE)
	{
		inletValveState = valveState;
	}
	else
	{
		outletValveState = valveState;
	}
	printf("the valve state is set! \n");
}

BOOL valveStatus (valveName_t valveName)
/* returns TRUE if the valve is opened and FALSE if not */
{
	printf( "returns the state of the valve - opened or closed \n");
	if(valveName == INLET_VALVE)
	{
		return inletValveState;
	}
	else
	{
		return outletValveState;
	}
} 

/* Interface for the sensors */
BOOL presenceDetected(sensorName_t sensorName)
{
	printf( "returns whether the sensor detected presence or not  \n");
	/* TODO: create mechanism that simulates the sensor state */
	return TRUE;
}

BOOL defectedProduct(sensorName_t sensorName)
{
	printf( "detects whether the product that passed in front of the sensor is defected or not  \n");
	/* TODO: create mechanism that simulates the defected product */
	return TRUE;
} 

/* Interface for the printers */
void setPrinterState(printerName_t printerName, BOOL printerState) 
{
	if(printerName == PRINTR1)
	{
		printer1State = printerState;
	}
	else
	{
		printer2State = printerState;
	}
	printf( "the printer state is set  \n");
} 

BOOL printerState(printerName_t printerName) 
{
	printf( "returns whether a printer is ready to print or not  \n");
	if(printerName == PRINTR1)
	{
		return printer1State;
	}
	else
	{
		return printer2State;
	}
} 

void print(printerName_t printerName, boxData_t boxData) 
{
	printf( "the box is being printed  \n");
} 

/* Interface for the lights */
void setColor(color_t color);
{
	lightsColor = color;
	printf( "the color is set  \n");
} 

color_t getColor();
{
	return lightsColor;
} 

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
			setColor(ORANGE)
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

#endif
