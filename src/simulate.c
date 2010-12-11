/* CIAI : DÃ©veloppement Multi-lots
* @author H4203
*
* This file contains a simulation routine.
*/

#include "simulate.h"

/* ------------------------------------------------------------
 * PRIVATE VARIABLES
 * ------------------------------------------------------------ */
static int _productCount = 0;


/* ------------------------------------------------------------
 * EXTERNAL FUNCTIONS (IT handlers to simulate)
 * ------------------------------------------------------------ */
 void EmergencyStopHandler ( );
 void ProductInflowHandler ( );


/* ------------------------------------------------------------
 * SIMULATION ROUTINE
 * ------------------------------------------------------------ */
void simulate (int updatesCount)
{
	if (updatesCount%PRODUCT_INFLOW_STEP == 0)
	{
		++_productCount;
		if (valveState(INLET_VALVE) == OPEN)
		{
			ProductInflowHandler();
		}
	}

	/* TODO simuler l'arrêt d'urgence */
	/*EmergencyStopHandler();*/
}


/* ------------------------------------------------------------
 * ACCESS FUNCTIONS
 * ------------------------------------------------------------ */
int generatedProductCount ()
{
	return _productCount;
}
