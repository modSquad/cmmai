/* CIAI : DÃ©veloppement Multi-lots
* @author H4203
*
* This file contains a task managing the simulator input.
*/

#include "simulatorControl.h"
#include "devices_simulation.h"


/* ------------------------------------------------------------
 * EXTERNAL FUNCTIONS (IT handlers to simulate)
 * ------------------------------------------------------------ */
void EmergencyStopHandler ( );


/* ------------------------------------------------------------
 * SCREEN OUTPUT CONSTANTS
 * ------------------------------------------------------------ */

#define SIMULATOR_PROMPT "\
\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\
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
Boxes will be missing:        %s\n\
============================================================\n\
Upcomming products:  %s\n\
\n\
Product count | Boxed  | Dropped | Total\n\
--------------+--------+---------+-------\n\
Correct       | %6d | %7d | %6d \n\
--------------+--------+---------+-------\n\
Defective     | %6d | %7d | %6d \n\
--------------+--------+---------+-------\n\
Total         | %6d | %7d | %6d \n\
============================================================\n\
Please enter a command and press <RETURN> : 
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
 * PRIVATE FUNCTIONS
 * ------------------------------------------------------------ */

void refreshScreen ( )
{
	char productsString[PRODUCTS_STRING_LENGTH + 1];
	int boxedCorrectProductCount = getBoxedProductCount(TRUE);
	int boxedDefectiveProductCount = getBoxedProductCount(FALSE);
	int droppedCorrectProductCount = getDroppedProductCount(TRUE);
	int droppedDefectiveProductCount = getDroppedProductCount(FALSE);

	getProductsString(productsString, PRODUCTS_STRING_LENGTH+1,
			CORRECT_PRODUCT_CHAR, DEFECTIVE_PRODUCT_CHAR);

	printf(SIMULATOR_PROMPT,
			COLOR_LABEL[getColor()],
			PRINTER_STATE_LABEL[printerState(PRINTR1)],
			PRINTER_STATE_LABEL[printerState(PRINTR2)],
			VALVE_STATE_LABEL[valveState(INLET_VALVE)],
			VALVE_STATE_LABEL[valveState(OUTLET_VALVE)],
			LAST_BOX_MISSING_LABEL[_lastBoxMissing],
			productsString,

			/*-- Product count table --*/
			/* 1st row */
			boxedCorrectProductCount,
			droppedCorrectProductCount,
			boxedCorrectProductCount + droppedCorrectProductCount,
			/* 2nd row */
			boxedDefectiveProductCount,
			droppedDefectiveProductCount,
			boxedDefectiveProductCount + droppedDefectiveProductCount,
			/* 3rd row */
			boxedCorrectProductCount + boxedDefectiveProductCount,
			droppedCorrectProductCount + droppedDefectiveProductCount,
			boxedCorrectProductCount + boxedDefectiveProductCount
				+ droppedCorrectProductCount + droppedDefectiveProductCount
			);
}


/* ------------------------------------------------------------
 * TASK
 * ------------------------------------------------------------ */

void simulatorInput ( )
{
	char inputChar;
	for ( ; ; )
	{
		scanf("%c",&inputChar);

		switch(inputChar)
		{
			case ADD_ONE_CORRECT_PRODUCT :
				addProducts(1, TRUE);
				break;
			case ADD_MANY_CORRECT_PRODUCTS :
				addProducts(MANY_MEANING, TRUE);
				break;
			case ADD_ONE_DEFECTIVE_PRODUCT :
				addProducts(1, TRUE);
				break;
			case ADD_MANY_DEFECTIVE_PRODUCTS :
				addProducts(MANY_MEANING, TRUE);
				break;
			case EMERGENCY_STOP :
				EmergencyStopHandler();
				break;
			case TOGGLE_MISSING_BOX :
				if (boxMissing())
				{
					setBoxMissing(FALSE);
				}
				else
				{
					setBoxMissing(TRUE);
				}
				break;
			case TOGGLE_PRINTR1_BROKEN :
				if (printerState(PRINTR1))
				{
					setPrinterState(FALSE);
				}
				else
				{
					setPrinterState(TRUE);
				}
				break;
			case TOGGLE_PRINTR2_BROKEN :
				if (printerState(PRINTR1))
				{
					setPrinterState(FALSE);
				}
				else
				{
					setPrinterState(TRUE);
				}
				break;
			case REFRESH :
			default :
				break;
		}

		refreshScreen();
	}
}

