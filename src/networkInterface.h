/*======================================================================*/
/*                                                                      */
/*                           networkInterface.h -  description                       */
/*                         ----------------------                       */
/*                                                                      */
/*======================================================================*/
/* ---------------  Interface de la tâche VxWorks <networkInterface> (fichier networkInterace.h) */
#ifndef NETWORK_INTERFACE_H
#define NETWORK_INTERFACE_H

/* -------------------------------------------------------------------- */
/* Rôle de la tâche <networkInterace>                                               */
/*                                                                      */
/* -------------------------------------------------------------------- */
/*                                                                      */
/* -------------------------------------------------------------INCLUDE */
/*                                                                      */
/* ------------------------------------------------Interfaces utilisées */

/*---------------------------------------------------------- Constantes */
#define NETWORK_SUCCESS 	0
#define NETWORK_ERROR 		-1
/*--------------------------------------------------------------- Types */

/* -------------------------------------------------------------------- */
/*                                                                      */
/*                                                               PUBLIC */
/*                                                                      */
/*------------------------------------------------- Variables publiques */

/*------------------------------------------------- Fonctions publiques */
int createServerSocket(int port);

int partAccepted(int fd);
int partRejected(int fd);

int sendError(int fd, int errCode);
int sendWarning(int fd, int errCode);

int sendLog(int fd, char* logMessage, int len);
/* -------------------------------------------------------------------- */
#endif // NETWORK_INTERFACE_H

