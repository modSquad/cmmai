/* CIAI : Développement Multi-lots
 * @author H4203
 *
 * This file contains common constants and objects shared between
 * modules.
 */

#ifndef BOXING_SERVER_H
#define BOXING_SERVER_H

/* Boolean type */
typedef enum
{
	FALSE,
	TRUE
} BOOL;

/*
 * Misc data types
 */
typedef unsigned int batchID_t;
typedef unsigned int boxID_t;
typedef unsigned int productsCount_t;

/**
 * Data allowing box tracing
 */
typedef struct
{
	batchID_t batchID;
	boxID_t boxID;
	productsCount_t boxedProducts;
		/* Count of correct products currently boxed */
	productsCount_t defectiveProducts;
		/* Count of defective products received when filling this box */
} boxData_t;

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

