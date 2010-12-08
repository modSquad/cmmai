/* CIAI : Développement Multi-lots
* @author H4203
*
* This file contains device access procedures.
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
	CLOSED,
	OPEN
} valveState_t;

typedef enum {
	BOX_PRESENCE_SENSOR
} presenceSensorName_t;
typedef enum {
	PRODUCT_DEFECT_SENSOR
} defectSensorName_t;

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
void setValveState(valveName_t valveName, valveState_t valveState);
	/* Open or close the valve.
	 * This function is non-blocking.
	 */
valveState_t valveState (valveName_t valveName);
	/* Returns the state of the valve - opened or closed */

/* Interface for the sensors */
BOOL presenceDetected(presenceSensorName_t sensorName); /* returns whether the sensor detected presence or not */
BOOL defectiveProduct(defectSensorName_t sensorName); /* detects whether the product that passed in front of the sensor is defected or not */

/* Interface for the printers */
BOOL printerState(printerName_t printerName); /* returns whether a printer is ready to print or not */
void print(printerName_t printerName, boxData_t boxData); /* sends the print command to the printer, the printer is unavailable while printing */

/* Interface for the lights */
void setColor(color_t color); /* Sets the color of the light device*/
color_t getColor();

#endif
