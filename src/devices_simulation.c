/* CIAI : Développement Multi-lots
* @author H4203
*
* This file contains simulated device access procedures, and a task
* managing the simulation update.
*/

#include <stdio.h>
#include <semLib.h>
#include <sysLib.h>
#include <stdlib.h>
#include <time.h>
#include "devices_simulation.h"

/* ------------------------------------------------------------
 * PRIVATE TYPES
 * ------------------------------------------------------------ */
typedef struct _products
{
	int amount;
	BOOL correctOnes;
	struct _products* next;
} _products;


/* ------------------------------------------------------------
 * STATIC VARIABLES
 * ------------------------------------------------------------ */

/* Upcoming products queue (linked list) */
static _products* _nextProducts = NULL;
static _products* _lastProducts = NULL;
static SEM_ID _mutex = NULL;

/* the light color */
static color_t _lightColor = GREEN;

/* the valves states */
static valveState_t _valveState[] =
{
		CLOSED, /* INLET_VALVE  */
		CLOSED  /* OUTLET_VALVE */
};

/* the printers states */
static BOOL _printerState[] =
{
		TRUE, /* NO_PRINTER */
		TRUE, /* PRINTR1 */
		TRUE  /* PRINTR2 */
};
/* the print counters */
static int _printCount[] =
{
		0, /* NO_PRINTER */
		0, /* PRINTR1 */
		0  /* PRINTR2 */
};

static BOOL _boxMissing = FALSE;

static int _boxedCorrectProductsCount =		0;
static int _boxedDefectiveProductsCount =	0;
static int _droppedCorrectProductsCount =	0;
static int _droppedDefectiveProductsCount =	0;


/* ------------------------------------------------------------
 * INTERFACE METHODS
 * ------------------------------------------------------------ */

/* Interface for the valves  - InletValve, OutletValve*/

void setValveState(valveName_t valveName, valveState_t valveState)
{
	_valveState[valveName] = valveState;
}

valveState_t valveState (valveName_t valveName)
{
	return _valveState[valveName];
}

/* Interface for the sensors */
BOOL presenceDetected(presenceSensorName_t sensorName)
{
	return !_boxMissing;
}

BOOL defectiveProduct(defectSensorName_t sensorName)
{
	/* We assume this will be called in a task calling a
	 * handler to simulate it, and not in a real IT handler.
	 * So blocking calls are allowed.
	 */
	BOOL result = TRUE;

	semTake(_mutex, WAIT_FOREVER);
	if (_nextProducts != NULL)
	{
		result = !_nextProducts->correctOnes;
	}
	semGive(_mutex);

	return result;
}

/* Interface for the printers */

BOOL printerState(printerName_t printerName)
{
	return _printerState[printerName];
}

void print(printerName_t printerName, const boxData_t* boxData)
{
	++_printCount[printerName];
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
 * SIMULATION ACCESS FUNCTIONS
 * ------------------------------------------------------------ */

void initDevicesSimulation ()
{
	srand(time(NULL));

	_mutex = semMCreate (SEM_Q_PRIORITY|SEM_DELETE_SAFE|SEM_INVERSION_SAFE);
}

void cleanDevicesSimulation ()
{
	_products* toDelete = NULL;

	while (_nextProducts != NULL)
	{
		toDelete = _nextProducts;
		_nextProducts = _nextProducts->next;
		free(toDelete);
	}
	_nextProducts = NULL;
	_lastProducts = NULL;

	semDelete(_mutex);
	_mutex = NULL;
}

void addProducts (int amount, BOOL correctProducts)
{
	_products* current = NULL;

	semTake(_mutex, WAIT_FOREVER);

	if (_nextProducts == NULL)
	{
		/* The list is empty, we have to add a new
		 * element */
		current = (_products*)malloc(sizeof(_products));
		_nextProducts = current;
		_lastProducts = current;
		current->correctOnes = correctProducts;
		current->amount = 0;
		current->next = NULL;
	}
	else
	{
		if (_lastProducts->correctOnes == correctProducts)
		{
			/* We can just add the amount to the last products */
			current = _lastProducts;
		}
		else
		{
			/* We have to add a new element to the tail */
			current = (_products*)malloc(sizeof(_products));
			_lastProducts->next = current;
			_lastProducts = current;
			current->correctOnes = correctProducts;
			current->amount = 0;
			current->next = NULL;
		}
	}

	current->amount += amount;

	semGive(_mutex);
}

BOOL upcomingProducts ()
{
	return _nextProducts != NULL;
}

void takeProduct ()
{
	semTake(_mutex, WAIT_FOREVER);

	if (_nextProducts != NULL)
	{
		/* Update the counters */
		if (_nextProducts->correctOnes)
		{
			if (_valveState[OUTLET_VALVE] == OPEN)
				++_droppedCorrectProductsCount;
			else
				++_boxedCorrectProductsCount;
		}
		else
		{
			if (_valveState[OUTLET_VALVE] == OPEN)
				++_droppedDefectiveProductsCount;
			else
				++_boxedDefectiveProductsCount;
		}

		/* Update the list */
		--_nextProducts->amount;
		if (_nextProducts->amount == 0)
		{
			_products *toDelete = _nextProducts;
			_nextProducts = _nextProducts->next;
			if (_nextProducts == NULL)
			{
				_lastProducts = NULL;
			}
			free(toDelete);
		}
	}

	semGive(_mutex);
}

void getProductsString (char buffer[], int bufferSize,
		 char correctProductChar, char defectiveProductChar)
{
	_products *current = NULL;

	--bufferSize; /* Handle the '\0' */

	semTake(_mutex, WAIT_FOREVER);

	current = _nextProducts;

	while (bufferSize > 0 && current != NULL)
	{
		int i;
		for ( i = 0 ; bufferSize > 0 && i < current->amount ; ++i )
		{
			*buffer = (current->correctOnes ?
					correctProductChar
					: defectiveProductChar);
			++buffer;
			--bufferSize;
		}
		current = current->next;
	}

	semGive(_mutex);

	*buffer = 0;
}

void setBoxMissing (BOOL boxMissing)
{
	_boxMissing = boxMissing;
}

BOOL boxMissing ()
{
	return _boxMissing;
}

void setPrinterState (printerName_t printerName, BOOL state)
{
	_printerState[printerName] = state;
}

int printCount (printerName_t printerName)
{
	return _printCount[printerName];
}

int boxedProductCount (BOOL correctOnes)
{
	if (correctOnes)
		return _boxedCorrectProductsCount;
	else
		return _boxedDefectiveProductsCount;
}

int droppedProductCount (BOOL correctOnes)
{
	if (correctOnes)
		return _droppedCorrectProductsCount;
	else
		return _droppedDefectiveProductsCount;
}


