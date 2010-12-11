/* CIAI : DÃ©veloppement Multi-lots
* @author H4203
*
* This file contains a task managing the simulator input.
*/

#ifndef SIMULATORCONTROL_H
#define SIMULATORCONTROL_H

#define ADD_ONE_CORRECT_PRODUCT			'a'
#define ADD_MANY_CORRECT_PRODUCTS		'A'
#define ADD_ONE_DEFECTIVE_PRODUCT		'q'
#define ADD_MANY_DEFECTIVE_PRODUCTS		'Q'
#define MANY_MEANING					10

#define EMERGENCY_STOP					's'
#define TOGGLE_MISSING_BOX				'm'
#define TOGGLE_PRINTR1_BROKEN			'p'
#define TOGGLE_PRINTR2_BROKEN			'P'

#define REFRESH							'r'

/** Process user commands.
 * The commands this task will understand are those
 * defined upper in this file.
 */
void simulatorInput ( );

#endif // SIMULATORCONTROL_H
