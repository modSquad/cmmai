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

/* --------------------------------------------------------- Constantes */
#define SERVER_WORK_PRIORITY 100 	/* priority of server's work task */
#define SERVER_STACK_SIZE 10000 	/* stack size of server's work task */
#define SERVER_MAX_CONNECTIONS 4 	/* max clients connected at a time */
#define REQUEST_MSG_SIZE 1024 		/* max size of request message */

/*
 * @brief Send data contained in buffer.
 * @param [in] fd : Client's file descriptor.
 * @param [in] buffer : Data to send.
 * @param [in] len : Buffer size.
 * @return : NETWORK_SUCCESS if data were sent without error. NETWORK_ERROR otherwise.
 */
static int sendData(const int fd, char* buffer,const int len){ /* PRIVATE */
	int sent = write(fd, buffer, len);
	return (sent == len) ? len : NETWORK_ERROR;
}

/*------------------------------------------------- Fonctions publiques */
int getClientSocket(int port) {
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

	/* validate client connection and store its file descriptor in newFd */
	if ((newFd = accept (fd, (struct sockaddr *) &clientAddr, &sockAddrSize)) == ERROR)
	{
		perror ("accept");
		close (fd);

		return NETWORK_ERROR;
	}

	return newFd;
}

int partAccepted(int fd, int n) {
	char msg[128]; /* In case of a reaaaaally big number ;) */
	int result, msgLen;
	sprintf(msg, "ACCEPTED\n%d\n\n", n); msgLen = strlen(msg);
	result = sendData(fd, msg, msgLen);

	return (result != msgLen) ? NETWORK_ERROR : NETWORK_SUCCESS;
}

int partRejected(int fd, int n) {
	char msg[128]; /* In case of a reaaaaally big number ;) */
	int result;
	sprintf(msg, "REJECTED\n%d\n\n", n);msgLen = strlen(msg);
	result = sendData(fd, msg, msgLen);

	return (result != msgLen) ? NETWORK_ERROR : NETWORK_SUCCESS;
}

int sendError(int fd, int errCode) {
	char msg[128]; /* In case of a reaaaaally big number ;) */
	int result;
	sprintf(msg, "ERROR\n%d\n\n", errCode);msgLen = strlen(msg);
	result = sendData(fd, msg, msgLen);

	return (result != msgLen) ? NETWORK_ERROR : NETWORK_SUCCESS;
}

int sendWarning(int fd, int errCode) {
	char msg[128]; /* In case of a reaaaaally big number ;) */
	int result;
	sprintf(msg, "WARNING\n%d\n\n", errCode);msgLen = strlen(msg);
	result = sendData(fd, msg, msgLen);

	return (result != msgLen) ? NETWORK_ERROR : NETWORK_SUCCESS;
}

int sendLog(int fd, char* logMessage, int len) {
	char msg[MIN_EVENT_STRING_BUFFER_SIZE + 9];
	int result;
	sprintf(msg, "ERROR\n%s\n\n", logMessage);msgLen = strlen(msg);
	result = sendData(fd, msg, msgLen);

	return (result != msgLen) ? NETWORK_ERROR : NETWORK_SUCCESS;
}

