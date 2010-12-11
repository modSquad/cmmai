/* CIAI : Développement Multi-lots
* @author H4203
*
* This file contains simulated device access procedures, and a task
* managing the simulation.
*/

#ifndef DEVICES_SIMULATION_H
#define DEVICES_SIMULATION_H

#include "devices.h"

/** Initialize the devices simulation.
 */
void initDevicesSimulation ();

/** Clean evereything that was done by the devices simulation.
 */
void cleanDevicesSimulation ();

/** Add products to the upcoming ones.
 * The products will be given to the system when all
 * those already added will have been taken.
 *
 * @param[in] amount The amount of products to add.
 * @param[in] correctProducts If FALSE, the added products
 *                            will be defective.
 */
void addProducts (int amount, BOOL correctProducts);

/** Take a product from the upcoming ones.
 */
void takeProduct ();

/** Get a string representation of upcomming products.
 * For example, if 2 correct products are coming, then a
 * defective one, then a correct one, then a defective one,
 * the following call:
 *  getProductsString(buffer, 10, 'O', 'X')
 * will result in the following string ('\0' included):
 *  "OOXOX"
 *
 * @param[in] buffer The buffer where the string will be stored.
 * @param[in] bufferSize The buffer size. Only the <bufferSize-1>
 *                       first product will be written. Must be
 *                       higher than 0 (not checked).
 * @param[in] correctProductChar The character that will represent
 *                               a correct product.
 * @param[in] defectiveProductChar The character that will represent
 *                                 a defective product.
 */
void getProductsString (char buffer[], int bufferSize,
		 char correctProductChar, char defectiveProductChar);

/** Set the state of the simulated box.
 * @param[in] boxMissing If TRUE, the subsequent calls
 *                       to presenceDetected will return FALSE
 */
void setBoxMissing (BOOL boxMissing);

/** Get the state of the simulated box.
 * @return The last value set by setBoxMissing.
 */
BOOL boxMissing ();

/** Set the printers states.
 * @param[in] printerName Excusively PRINTR1 or PRINTR2 (not checked)
 * @param[in] state The printer state.
 */
void setPrinterState (printerName_t printerName, BOOL state);

/** Get the boxed product count.
 *
 * @param[in] correctOnes Select the count that will be returned :
 *                        correct (correctOnes = TRUE) products count or
 *                        defective (correctOnes = FALSE) products count
 *
 * @return The asked product count.
 */
int boxedProductCount (BOOL correctOnes);

/** Get the dropped product count.
 *
 * @param[in] correctOnes Select the count that will be returned :
 *                        correct (correctOnes = TRUE) products count or
 *                        defective (correctOnes = FALSE) products count
 *
 * @return The asked product count.
 */
int droppedProductCount (BOOL correctOnes);

#endif
