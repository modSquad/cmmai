/* CIAI : Développement Multi-lots
* @author H4203
*
* This file contains simulation procedures of the devices used by our application.
* 
*/

#ifndef DEVICES_H
#define DEVICES_H

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
void closeValve(valveName_t valveName); /*  closes the valve */
void openValve(valveName_t valveName); /*  opens the valve */
bool valveStatus (valveName_t valveName); /* returns the state of the valve - opened or closed */

/* Interface for the sensors */
bool presenceDetected(sensorName_t sensorName); /* returns whether the sensor detected presence or not */
bool defectedProduct(sensorName_t sensorName); /* detects whether the product that passed in front of the sensor is defected or not */

/* Interface for the printers */
bool printerState(printerName_t printerName); /* returns whether a printer is ready to print or not */
void print(printerName_t printerName, boxData_t boxData); /* sends the print command to the printer, the printer is unavailable while printing */

/* Interface for the lights */
void setColor(color_t color); /* Sets the color of the light device*/


#endif