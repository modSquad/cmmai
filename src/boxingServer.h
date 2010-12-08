/* CIAI : Développement Multi-lots
 * @author H4203
 *
 * This file contains common constants and objects shared between
 * modules.
 */

#ifndef BOXING_SERVER_H
#define BOXING_SERVER_H

typedef int BOOL;

/*
 * Misc data types
 */
typedef unsigned long batchID_t;
typedef unsigned long boxID_t;
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
 * boxingEvent_t represent an event happening in the application.
 */
typedef enum
{
	/* Dummy value for a dummy event */
	EVT_NONE,
	/* Sent by NetworkListener when start requested  by user via network*/
	EVT_APPLICATION_START,
	/* Sent by NetworkListener when stop requested  by user via network*/
	EVT_APPLICATION_STOP,
	/* Sent by BoxManager when it stops managing box filling due to
	 * application end request
	 */
	EVT_END_FILLING,
	/* Sent by PrintManager when it receives the end application flag */
	EVT_CLOSE_APPLICATION, 
	/* Sent by EmergencyStopHandler when activated */
	EVT_EMERGENCY_STOP, 
	/* Sent by BoxManager when a box is filled and sent to the printer queue */
	EVT_BOX_PROCESSED, 
	/* Sent by PrintManager when a box has been printed */
	EVT_BOX_PRINTED, 
	/* Sent by PrintManager when a printer doesn't work */
	EVT_ANOMALY_PRINTER1, 
	EVT_ANOMALY_PRINTER2,
	/* Sent by ProductInflow when the treshold of defective products is reached */
	EVT_ERR_DEFECTIVE_TRESHOLD_REACHED,
	/* Sent by Box Manager when the queue containing the boxes to be printed is
	 * full (it already contains 5 boxes) */
	EVT_ERR_FULL_QUEUE, 
	/* Sent by BoxManager when the box is not present */
	EVT_ERR_BOX_STARVATION, 
	/* Sent by ProductStarvationHandler when there is a product famine */
	EVT_ERR_PRODUCT_STARVATION 
} boxingEvent_t;

/**
 * Type of a message in the events queue.
 */
typedef struct
{
	boxingEvent_t event;
	boxData_t boxData;
} event_msg_t;

/**
 * Type of a message in the boxes queue.
 */
typedef struct
{
	BOOL lastMessage;
	boxData_t boxData;
} boxesQueueMsg_t;

/**
 * Size of the boxes queue before printing operations
 */
static const int MAX_BOXES_QUEUE_SIZE = 5;

#endif

