/* -------------------------------------------------------------------- */
/*                                                                      */
/*                    <networkInterface>.c  -  description                           */
/*                        -----------------------                       */
/*                                                                      */
/* -------------------------------------------------------------------- */
/*                                                                      */
/*    Realisation de la tache VxWorks <networkInterface>.c      */
/*                                                                      */
/* -------------------------------------------------------------------- */
/* ------------------------------------------------------------ INCLUDE */
/* ---------------------------------------------------- Include système */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <sockLib.h>
#include <taskLib.h>
#include <inetLib.h>
#include <fioLib.h>

#include "networkInterface.h"
#include "eventToString.h"

/* -------------------------------------------------- Include personnel */

/* -------------------------------------------------------------------- */
/*                                                                      */
/*                        PRIVE                                         */
/*                                                                      */
/* --------------------------------------------------------- Constantes */

#define SERVER_WORK_PRIORITY 100 	/* priority of server's work task */
#define SERVER_STACK_SIZE 10000 	/* stack size of server's work task */
#define SERVER_MAX_CONNECTIONS 4 	/* max clients connected at a time */
#define REQUEST_MSG_SIZE 1024 		/* max size of request message */
/* -------------------------------------------------------------- Types */


/* -------------------------------------------------- Variables privees */


/*--------------------------------------------------- Fonctions privees */
/*
 * Envoie les donn'ees contenues dans le buffer pass'e en param`etre 
 * sur le fichier fd pass'e en param`etre.
 * La fonction revoie : 	len si l''echange s'est bien pass'e.
 * 							NETWORK_ERROR sinon
 */
static int sendData(const int fd, char* buffer,const int len){
	int sent = write(fd, buffer, len);
	return (sent == len) ? len : NETWORK_ERROR;
}

/* -------------------------------------------------------------------- */
/*                                                                      */
/*                        PUBLIC                                        */
/*                                                                      */
/* ------------------------------------------------ Variables publiques */

/*------------------------------------------------- Fonctions publiques */
/*
 * This method create a server socket and bind it on the specified port.\
 * If the socket is effectively created and binded, the file descriptor is returned.
 * Otherwise, NETWORK_ERROR is resurned
 */
int createServerSocket(int port) {
	struct sockaddr_in serverAddr; /* server's socket address */
	int sockAddrSize; /* size of socket address structure */ 
	int fd; /* socket file descriptor */
	int newFd = -1;
	struct sockaddr_in clientAddr; /* client's socket address */
	
	/* set up the local address */
	sockAddrSize = sizeof (struct sockaddr_in);
	memset((char *) &serverAddr, 0, sockAddrSize);
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_len = (u_char) sockAddrSize;
	serverAddr.sin_port = htons (port);
	serverAddr.sin_addr.s_addr = htonl (INADDR_ANY);
	
	/* create a TCP-based socket */
	if ((fd = socket (AF_INET, SOCK_STREAM, 0)) == ERROR)
	{
		perror ("socket");
		return NETWORK_ERROR;
	}
	
	/* bind socket to local address */
	if (bind (fd, (struct sockaddr *) &serverAddr, sockAddrSize) == ERROR)
	{
		perror ("bind");
		close (fd);
		
		return NETWORK_ERROR;
	}
	
	/* create queue for client connection requests */
	if (listen (fd, SERVER_MAX_CONNECTIONS) == ERROR)
	{
		perror ("listen");
		close (fd);
		
		return NETWORK_ERROR;
	}
	
	if ((newFd = accept (fd, (struct sockaddr *) &clientAddr, &sockAddrSize)) == ERROR)
	{
		perror ("accept");
		close (fd);
		
		return NETWORK_ERROR;
	}
	
	return newFd;
}

int partAccepted(int fd) {
	char msg[] = "ACCEPTED\n\n";
	int result = sendData(fd, msg, strlen(msg));
	
	return (result == NETWORK_ERROR) ? NETWORK_ERROR : NETWORK_SUCCESS;
}

int partRejected(int fd) {
	char msg[] = "REJECTED\n\n";
	int result = sendData(fd, msg, strlen(msg));
	
	return (result == NETWORK_ERROR) ? NETWORK_ERROR : NETWORK_SUCCESS;
}

int sendError(int fd, int errCode) {
	char msg[128];
	int result;
	sprintf(msg, "ERROR\n%d\n\n", errCode);
	result = sendData(fd, msg, strlen(msg));
	
	return (result == NETWORK_ERROR) ? NETWORK_ERROR : NETWORK_SUCCESS;
}

int sendWarning(int fd, int errCode) {
	char msg[128];
	int result;
	sprintf(msg, "WARNING\n%d\n\n", errCode);
	result = sendData(fd, msg, strlen(msg));
	
	return (result == NETWORK_ERROR) ? NETWORK_ERROR : NETWORK_SUCCESS;
}

int sendLog(int fd, char* logMessage, int len) {
	char msg[MIN_EVENT_STRING_SIZE + 128];
	int result;
	sprintf(msg, "ERROR\n%s\n\n", logMessage);
	result = sendData(fd, msg, strlen(msg));
	
	return (result == NETWORK_ERROR) ? NETWORK_ERROR : NETWORK_SUCCESS;
}
/* -------------------------------------------------------------------- */
