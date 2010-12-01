/* CIAI : Développement Multi-lots
 * @author H4203
 *
 * This file contains common constants and objects shared between
 * modules.
 */

#ifndef BOXING_SERVER_H
#define BOXING_SERVER_H

/**
 * event_t represent an event happening in the application.
 */
typedef enum {
	/**
	 * Dummy value for a dummy event.
	 */
	EVT_NONE
	
} event_t;

/**
 * error_t represent an error occuring in the application.
 */
typedef enum {
	/**
	 * Value meaning there is no error
	 */
	ERR_NONE
} error_t;

#endif

