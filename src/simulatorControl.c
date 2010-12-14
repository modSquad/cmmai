/* CIAI : DÃ©veloppement Multi-lots
* @author H4203
*
* This file contains a task managing the simulator input.
*/

#include <stdio.h>
#include "simulatorControl.h"
#include "devices_simulation.h"


/* ------------------------------------------------------------
 * EXTERNAL FUNCTIONS (IT handlers to simulate)
 * ------------------------------------------------------------ */
void EmergencyStopHandler ( );


/* ------------------------------------------------------------
 * SCREEN OUTPUT CONSTANTS
 * ------------------------------------------------------------ */

#define PRODUCTS_STRING_LENGTH	30
#define CORRECT_PRODUCT_CHAR	'O'
#define DEFECTIVE_PRODUCT_CHAR	'X'
#define NONE_STRING				"None"

#define SIMULATOR_PROMPT "\
\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\
Simulator v1.0\n\
\n\
\n\
============================================================\n\
Light:         %s\n\
============================================================\n\
Valve     | Inlet  | Outlet \n\
----------+--------+--------\n\
Status    | %6s | %6s \n\
============================================================\n\
Printer #   |    1    |    2    \n\
------------+---------+---------\n\
Status      | %7s | %7s \n\
------------+---------+---------\n\
Print count | %7d | %7d \n\
============================================================\n\
Boxes will be missing:        %s\n\
============================================================\n\
Upcoming products:  %s\n\
\n\
Product count | Boxed  | Dropped | Total\n\
--------------+--------+---------+-------\n\
Correct       | %6d | %7d | %6d \n\
--------------+--------+---------+-------\n\
Defective     | %6d | %7d | %6d \n\
--------------+--------+---------+-------\n\
Total         | %6d | %7d | %6d \n\
============================================================\n\
Please enter a command and press <RETURN> : \
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
	int boxedCorrectProductCount = boxedProductCount(TRUE);
	int boxedDefectiveProductCount = boxedProductCount(FALSE);
	int droppedCorrectProductCount = droppedProductCount(TRUE);
	int droppedDefectiveProductCount = droppedProductCount(FALSE);

	getProductsString(productsString, PRODUCTS_STRING_LENGTH+1,
			CORRECT_PRODUCT_CHAR, DEFECTIVE_PRODUCT_CHAR);

	printf(SIMULATOR_PROMPT,
			COLOR_LABEL[getColor()],
			VALVE_STATE_LABEL[valveState(INLET_VALVE)],
			VALVE_STATE_LABEL[valveState(OUTLET_VALVE)],
			PRINTER_STATE_LABEL[printerState(PRINTR1)],
			PRINTER_STATE_LABEL[printerState(PRINTR2)],
			printCount(PRINTR1),
			printCount(PRINTR2),
			LAST_BOX_MISSING_LABEL[boxMissing()],
			(productsString[0] == 0 ? NONE_STRING : productsString),

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

int simulatorControl ( )
{
	char inputChar;

	refreshScreen();
	
	inputChar = getchar();
	while (inputChar != EOF)
	{
		/*if (scanf("%c",&inputChar) < 0)
		{
			perror("Simulator input error:");
		}*/

		switch(inputChar)
		{
			case ADD_ONE_CORRECT_PRODUCT :
				addProducts(1, TRUE);
				break;
			case ADD_MANY_CORRECT_PRODUCTS :
				addProducts(MANY_MEANING, TRUE);
				break;
			case ADD_ONE_DEFECTIVE_PRODUCT :
				addProducts(1, FALSE);
				break;
			case ADD_MANY_DEFECTIVE_PRODUCTS :
				addProducts(MANY_MEANING, FALSE);
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
					setPrinterState(PRINTR1,FALSE);
				}
				else
				{
					setPrinterState(PRINTR1,TRUE);
				}
				break;
			case TOGGLE_PRINTR2_BROKEN :
				if (printerState(PRINTR2))
				{
					setPrinterState(PRINTR2,FALSE);
				}
				else
				{
					setPrinterState(PRINTR2,TRUE);
				}
				break;
			case REFRESH :
			default :
				break;
		}

		refreshScreen();
		
		inputChar = getchar();
	}
	
	return 0;
}

