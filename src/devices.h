/* CIAI : Développement Multi-lots
* @author H4203
*
* This file contains simulation procedures of the devices used by our application.
* 
*/

#ifndef DEVICES_H
#define DEVICES_H

#include "boxingServer.h"

typedef enum {
	INLET_VALVE,
	OUTLET_VALVE
} valveName_t;

typedef enum {
	BOX_PRESENCE_SENSOR,
	PRODUCT_DEFECT_SENSOR
} sensorName_t;

typedef enum {
	PRINTR1,
	PRINTR2
} printerName_t;

typedef enum {
	RED,
	GREEN,
	ORANGE
} color_t;

/* Interface for the valves  - InletValve, OutletValve*/
void setValveState(valveName_t valveName, BOOL valveState);
BOOL valveStatus (valveName_t valveName); /* returns the state of the valve - opened or closed */

/* Interface for the sensors */
BOOL presenceDetected(sensorName_t sensorName); /* returns whether the sensor detected presence or not */
BOOL defectedProduct(sensorName_t sensorName); /* detects whether the product that passed in front of the sensor is defected or not */

/* Interface for the printers */
void setPrinterState(printerName_t printerName, BOOL newPrinterState); /* sets the state of a printer - ready to print or not */
BOOL printerState(printerName_t printerName); /* returns whether a printer is ready to print or not */
void print(printerName_t printerName, boxData_t boxData); /* sends the print command to the printer, the printer is unavailable while printing */

/* Interface for the lights */
void setColor(color_t color); /* Sets the color of the light device*/
color_t getColor();
void setLight(boxingEvent_t event); /* Determine and set the color with an event */

#endif
