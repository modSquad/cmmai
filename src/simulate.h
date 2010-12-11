/* CIAI : DÃ©veloppement Multi-lots
* @author H4203
*
* This file contains a simulation routine.
*/

#ifndef SIMULATE_H
#define SIMULATE_H

#define PRODUCT_INFLOW_STEP 10

/* Generate ITs.
 * If the parameter is a multiple of PRODUCT_INFLOW_STEP,
 * this function will call the InflowHandler.
 * TODO emergencyStop ?
 */
void simulate (int updatesCount);

/* Get the count of generated products.
 *
 * @return The count of generated products so far.
 */
int generatedProductCount ();

#endif // SIMULATE_H

