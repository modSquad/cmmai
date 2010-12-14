/* CIAI : DÃ©veloppement Multi-lots
* @author H4203
*
* This file contains the task simulating product inflow.
*/

#include <taskLib.h>
#include <sysLib.h>
#include "simulatorUpdater.h"
#include "devices_simulation.h"

/* ------------------------------------------------------------
 * EXTERNAL FUNCTIONS (IT handlers to simulate)
 * ------------------------------------------------------------ */
void ProductInflowHandler ( );

/* ------------------------------------------------------------
 * TASK
 * ------------------------------------------------------------ */
int simulatorUpdater (int productGenerationDelay)
{
	BOOL productIsOK;

	for ( ; ; )
	{
		taskDelay(productGenerationDelay);

		if (upcomingProducts() && valveState(INLET_VALVE) == OPEN)
		{
			ProductInflowHandler();
			takeProduct();
		}
	}
	
	return 0;
}

