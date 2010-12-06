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
typedef unsigned int boxCount_t;

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
 * Application settings data structure
 */
typedef struct
{
	BOOL applicationEndRequest;
		/* TRUE when the user asked for the application to end. */
	batchID_t batchID;
		/* ID given by user */
	boxCount_t batchBoxesCount;
		/* Current count of filled boxes for this batch. */
	boxCount_t batchBoxesAsked;
		/* Number of boxes we have to fill for this batch. */
	productsCount_t productsPerBox;
		/* Number of products to put in each box. */
	productsCount_t maxDefectiveProductsPerBox;
		/* Number of admitted defective products for each box. */
} settings_t;

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

/**
 * Size of the boxes queue before printing operations
 */
static const int MAX_BOXES_QUEUE_SIZE = 5;

#endif

