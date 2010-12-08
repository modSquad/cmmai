/* CIAI : Développement Multi-lots
 * @author H4203
 */

#ifndef NETWORK_INTERFACE_H
#define NETWORK_INTERFACE_H

/*---------------------------------------------------------- Constantes */
#define NETWORK_SUCCESS 	0  /* If no error were detected */
#define NETWORK_ERROR 		-1 /* If error were detected */

/*
 * @brief Create a server socket on the specified port and wait for a client.
 * When a client tries to connect, connection is accepted, and client socket is returned.
 * @param [in] port : Port on which the server socket will listen while waiting for a client.
 * @return : File descriptor corresponding to the client socket after connection is established.
 */
int getClientSocket(int port);

/*
 * @brief Send part acception information to the client. 
 * @param [in] fd : Client file descriptor in which information is written.
 * @param [int] n : Number of accepted part.
 * @return : NETWORK_SUCCESS if data were sent without error. NETWORK_ERROR otherwise.
 */
int partAccepted(int fd, int n);

/*
 * @brief Send part rejection information to the client. 
 * @param [in] fd : Client file descriptor in which information is written.
 * @param [int] n : Number of rejected part.
 * @return : NETWORK_SUCCESS if data were sent without error. NETWORK_ERROR otherwise.
 */
int partRejected(int fd, int n);

/*
 * @brief Send error information to the client.
 * @param [in] fd : Client file descriptor in which information is written.
 * @param [in] errCode : Error code sent.
 * @return : NETWORK_SUCCESS if data were sent without error. NETWORK_ERROR otherwise.
 */ 
int sendError(int fd, int errCode);

/*
 * @brief Send warning information to the client.
 * @param [in] fd : Client file descriptor in which information is written.
 * @param [in] errCode : Warning code sent.
 * @return : NETWORK_SUCCESS if data were sent without warning. NETWORK_warning otherwise.
 */ 
int sendWarning(int fd, int errCode);

/*
 * @brief Send log data to the client.
 * @param [in] fd : Client file descriptor in which information is written.
 * @param [in] logMessage : Content of the log message.
 * @param [in] len : Length of the log message.
 * @return : NETWORK_SUCCESS if data were sent without warning. NETWORK_warning otherwise.
 */
int sendLog(int fd, char* logMessage, int len);
#endif // NETWORK_INTERFACE_H

