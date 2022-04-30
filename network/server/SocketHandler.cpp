/*
 * SocketHandler.cpp
 *
 *  Created on: Apr 27, 2022
 *      Author: Michael Bloom & Andrew Juhola
 */

//Implementation of header file.
#include "SocketHandler.h"

//Netowork Libraries
#include "../utilities/Logger.h"	//For logging.

//POSIX Libraries
#include "netinet/in.h"	//For retrieving socket addresses.
#include "sys/socket.h"	//For creating addresses.
#include "unistd.h"		//For
#include "fcntl.h"

//Standard C++ Libraries
#include <string>	//For handling strings.

//Standard C Libraries
#include <cstring>		//For memset.

//Macros
#define SOCKET_ERROR -1	//For handling POSIX errors.

SocketHandler::SocketHandler() {

}

SocketHandler::~SocketHandler() {
	// TODO Auto-generated destructor stub
}

int SocketHandler::createServerSocket(int domain, int type, int port, int backlog){
	//Declare an address struct for the socket.
	struct sockaddr_in address = this->createAddress();

	//Assign attributes to the address.
	address.sin_family = domain;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);

	//Create the socket and return the descriptor.
	int sockfd = socket(domain, type, 0);

	//Check the file descriptor.
	if(SOCKET_ERROR == sockfd){
		std::logic_error e("Could not create client descriptor.");
		throw(e);
	}

	//Bind the socket.
	if(SOCKET_ERROR == bind(sockfd, (struct sockaddr *) &address, sizeof(address))){
		std::logic_error e("Could not bind socket to address.");
		throw(e);
	}

	//Add a listener to the socket.
	if(SOCKET_ERROR == listen(sockfd, backlog)){
		std::logic_error e("Could not create listener.");
		throw(e);
	}

	//Log socket information.
	Logger::logSection("Socket Information");
	Logger::logInfo("Descriptor: " + std::to_string(sockfd));
	Logger::logInfo("Address: " + std::to_string(address.sin_addr.s_addr));
	Logger::logInfo("Port: " + std::to_string(port));
	Logger::endSection();

	return sockfd;
}

int SocketHandler::createClientSocket(int sockfd, socketInfo *info){
	//Declare an address struct for the socket.
	struct sockaddr_in address = this->createAddress();
	socklen_t length = sizeof(address);

	//Create the socket and return the descriptor.
	int clientfd = accept(sockfd, (struct sockaddr*) &address, &length);

	//Check the file descriptor.
	if(SOCKET_ERROR == clientfd){
		std::logic_error e("Could not create client descriptor.");
		throw(e);
	}

	//Set the non-blocking.
	if(SOCKET_ERROR == fcntl(clientfd, F_SETFL, O_NONBLOCK)){
		std::logic_error e("Could not block.");
		throw(e);
	}

	info->ip = address.sin_addr.s_addr;
	info->port = address.sin_port;

	//Log client information.
	Logger::logSection("Client Information");
	Logger::logInfo("Descriptor: " + std::to_string(clientfd));
	Logger::logInfo("IP: " + std::to_string(info->ip));
	Logger::logInfo("Port: " + std::to_string(info->port));
	Logger::endSection();

	return clientfd;

}

void SocketHandler::closeSocket(int fileDescriptor){
	close(fileDescriptor);
}

struct sockaddr_in SocketHandler::createAddress(){
	struct sockaddr_in address;
	memset(&address, 0, sizeof(address));
	return address;
}
