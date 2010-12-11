/* CIAI : DÃ©veloppement Multi-lots
* @author H4203
*
* This file contains the task simulating product inflow.
*/

#ifndef SIMULATORUPDATER_H
#define SIMULATORUPDATER_H

#define PRODUCT_INFLOW_STEP 10

/**
 * Simulate a production environment.
 *
 * The simulator updater will call periodically the ProductInflowHandler
 * and update devices accordingly.
 * In order to work properly, this task has to have a higher priority than
 * all the application tasks.
 * It should have the same priority than simulatorInput.
 *
 * @param[in] ticksStep Number of system clock ticks between two products.
 */
void simulatorUpdater (int ticksStep);

#endif // SIMULATORUPDATER_H

