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

//Standard C++ Libararies
#include <string>	//For handling strings.
#include <memory>	//For handling prointers

//Macros
#define SOCK_CLIENT 0		//Create a client socket.
#define SOCK_SERVER_TCP 1	//Create a server socket with TCP.

//Struct for collecting socket info.
typedef struct socketInfo {
	int ip;
	int port;
} socketInfo;

class SocketHandler {

	private:
		int socketfd;
		socketInfo sockInfo;

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
		 */
		void createServerSocket(int domain, int type, int port, int backlog);

		/**
		 * Creates a client socket.
		 * @param int is the server socket descriptor.
		 * @param socketInfo is a structure for sending info about the client to.
		 * @return std::shared_ptr<SocketHandler> is the client socket.
		 */
		std::shared_ptr<SocketHandler> createClientSocket();


		/**
		 * Closes the server socket.
		 */
		void closeSocket();

		/**
		 * Gets a message from the client.
		 * @param std::string is the message from the client.
		 */
		std::string receiveMessage();

		/**
		 * Sends a message from to the client.
		 * @param std::string is the message from the client.
		 */
		void sendMessage(std::string message);

		/**
		 * Retreives the client information.
		 * @return socketInfo is the information for the client socket.
		 */
		socketInfo getSocketInfo();

	//Utilities
	private:

		/**
		 * Creates an address.
		 * @return struct sockaddr_in is the address.
		 */
		struct sockaddr_in createAddress();

		/**
		 * Creates poll requests.
		 * @param int is the socket descriptor for polling.
		 */
		void pollRequest(int socketfd);

};

#endif /* SOCKETHANDLER_H_ */
