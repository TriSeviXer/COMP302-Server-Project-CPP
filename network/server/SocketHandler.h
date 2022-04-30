/*
 * SocketHandler.h
 *
 *  Created on: Apr 27, 2022
 *      Author: Michael Bloom & Andrew Juhola
 */

#ifndef SOCKETHANDLER_H_
#define SOCKETHANDLER_H_

//POSIX Libraries
#include "netinet/in.h"	//For retrieving socket addresses.

//Macros
#define SOCK_CLIENT 0		//Create a client socket.
#define SOCK_SERVER_TCP 1	//Create a server socket with TCP.

//Struct for collecting socket info.
typedef struct socketInfo {
	int ip;
	int port;
} socketInfo;

class SocketHandler {

	//Constructors and Destructors.
	public:
		SocketHandler();
		virtual ~SocketHandler();

	//Functions
	public:

		/**
		 * Creates a server socket.
		 * @param int is the domain.
		 * @param int is the protocol used.
		 * @param int is the port number.
		 * @param int is the number of connections for the socket.
		 * @return int is the socket descriptor.
		 */
		int createServerSocket(int domain, int type, int port, int backlog);

		/**
		 * Creates a client socket.
		 * @param int is the server socket descriptor.
		 * @param socketInfo is a structure for sending info about the client to.
		 * @return int is the client descriptor.
		 */
		int createClientSocket(int sockfd, socketInfo *info);

		/**
		 * Cloeses a socket.
		 * @return int is the file descriptor.
		 */
		void closeSocket(int fileDescriptor);

	//Utilities
	private:

		/**
		 * Creates an address.
		 * @return struct sockaddr_in is the address.
		 */
		struct sockaddr_in createAddress();
};

#endif /* SOCKETHANDLER_H_ */
