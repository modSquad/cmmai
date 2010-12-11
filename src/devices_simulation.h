/* CIAI : Développement Multi-lots
* @author H4203
*
* This file contains simulated device access procedures, and a task
* managing the simulation.
*/

#ifndef DEVICES_SIMULATION_H
#define DEVICES_SIMULATION_H

#include "devices.h"

/**
 * Simulate a production environment.
 *
 * The simulator will set up the configuration for all environment variables
 * (sensor values, product inflow rate, ...) and then trigger periodically
 * a callback function (<simulateCallBack(int)>) and give a periodical
 * screen output of the current state of the environment.
 * In order to work properly, this task has to have a
 * higher priority than all the application tasks.
 *
 * @param[in] simulationCallBack A callback function that will be called
 *                               periodically. It's given one arguments :
 *                               the number of previous calls.
 *                               Must be non-NULL. (no check)
 * @param[in] updateDelay Delay between two callbacks (in seconds).
 *                        The system clock rate must have been set accordingly.
 *                        Must be higher than 0. (no check)
 * @param[in] screenRefreshStep Number of updates (callbacks) between
 *                              two screen refreshes.
 *                              Must be higher than 0. (no check)
 * @param[in] defectRate At each call to <defectiveProduct>, we'll have
 *                       one in <defectRate> chance to answer TRUE.
 *                       If null, no product will ever be defective.
 *                       Must be higher than 0 or null. (no check)
 * @param[in] missingBoxRate At each call to <presenceDetected>, we'll have
 *                           one in <defectRate> chance to answer FALSE.
 *                           If null, no box will ever be missing.
 *                           Must be higher than 0 or null. (no check)
 * @param[in] brokenPrinterRate At each call to <printerState>, we'll have
 *                              one in <brokenPrinterRate> chance to answer BROKEN.
 *                              If null, no printer will ever be broken.
 *                              Must be higher than 0 or null. (no check)
 */
void simulator (
		void (*simulationCallBack)(int),
		double updateDelay, int screenRefreshStep,
		int defectRate, int missingBoxRate, int brokenPrinterRate,
		)

#endif
