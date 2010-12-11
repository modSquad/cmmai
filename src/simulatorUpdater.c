/* CIAI : DÃ©veloppement Multi-lots
* @author H4203
*
* This file contains the task simulating product inflow.
*/

#include "simulationUpdater.h"

/* ------------------------------------------------------------
 * EXTERNAL FUNCTIONS (IT handlers to simulate)
 * ------------------------------------------------------------ */
void ProductInflowHandler ( );

/* ------------------------------------------------------------
 * TASK
 * ------------------------------------------------------------ */
void simulatorUpdater (int productGenerationDelay)
{
	BOOL productIsOK;

	for ( ; ; )
	{
		taskDelay((int)(productGenerationDelay*sysClkRateGet()));

		if (valveState(INLET_VALVE) == OPEN)
		{
			ProductInflowHandler();
			takeProduct();
		}
	}
}

