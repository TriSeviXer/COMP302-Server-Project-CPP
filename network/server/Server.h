/*
 * Server.h
 *
 *  Created on: Mar 28, 2022
 *      Author: Michael Bloom & Andrew Juhola
 */

#ifndef SERVER_H_
#define SERVER_H_

//Network Libraries
#include "SocketHandler.h"	//For socketInfo structure.

//Standard C++ Libraries
#include <memory>	//For memory management.
#include <string>	//For handling strings.

class Server {
	//Variables and constants.
	private:
		std::string serverName;
		int domain;
		int type;
		int portNumber;
		int backlog;

	//Constructor and destructor.
	public:
		Server();
		virtual ~Server();

	//Server functions.
	public:

		/**
		 * Initializes and runs the server.
		 */
		void run();

		/**
		 * Sets the name of the server.
		 * @param name is the name used for the server.
		 * @return server object,
		 */
		Server* setName(std::string name);

		/**
		 * Sets the port number for the server.
		 * @param portNumber is the port used for the server.
		 * @return server object.
		 */
		Server* setPort(int portNumber);

		/**
		 * Sets the max connections to the server.
		 * @param backlog is the number of connections that can be made to the server.
		 * @return server object.
		 */
		Server* setBacklog(int backlog);

	private:

		/**
		 * Creates poll requests.
		 * @param clientfd is the client being polled.
		 */
		void pollRequest(int clientfd);

		/**
		 * Processes a client message.
		 * @param socketInfo is the structure for client information.
		 * @param std::string is the message from the client.
		 * @return std::string message return from the server.
		 */
		std::string processMessage(socketInfo clientInfo, std::string message);

		/**
		 * Gets a message from the client.
		 * @param int is the client descriptor.
		 * @param std::string is the message from the client.
		 */
		std::string receiveMessage(int clientfd);

		/**
		 * Sends a message from to the client.
		 * @param int is the client descriptor.
		 * @param std::string is the message from the client.
		 */
		void sendMessage(int clientfd, std::string message);

};

#endif /* SERVER_H_ */
