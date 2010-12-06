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
	EVT_NONE, /* Dummy value for a dummy event. */
	EVT_BOX_PROCESSED,
		/* Sent by BoxHandler when a box is filled and sent to the queue */
	EVT_ERR_BOX_STARVATION,
	EVT_ERR_PRODUCT_STARVATION
} event_t;

#endif

