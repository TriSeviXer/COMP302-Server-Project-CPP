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
#include "poll.h"		//For polling messages.
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

}

void SocketHandler::createServerSocket(int domain, int type, int port, int backlog){
	//Declare an address struct for the socket.
	struct sockaddr_in address = this->createAddress();

	//Assign attributes to the address.
	address.sin_family = domain;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);

	//Create the socket and return the descriptor.
	this->sockfd = socket(domain, type, 0);

	//Check the file descriptor.
	if(SOCKET_ERROR == this->sockfd){
		std::logic_error e("Could not create client descriptor.");
		throw(e);
	}

	//Bind the socket.
	if(SOCKET_ERROR == bind(this->sockfd, (struct sockaddr *) &address, sizeof(address))){
		std::logic_error e("Could not bind socket to address.");
		throw(e);
	}

	//Add a listener to the socket.
	if(SOCKET_ERROR == listen(this->sockfd, backlog)){
		std::logic_error e("Could not create listener.");
		throw(e);
	}

	//Log socket information.
	Logger::logSection("Socket Information");
	Logger::logInfo("Descriptor: " + std::to_string(this->sockfd));
	Logger::logInfo("Address: " + std::to_string(address.sin_addr.s_addr));
	Logger::logInfo("Port: " + std::to_string(port));
	Logger::endSection();

}

void SocketHandler::createClientSocket(){
	//Declare an address struct for the socket.
	struct sockaddr_in address = this->createAddress();
	socklen_t length = sizeof(address);

	//Create the socket and return the descriptor.
	this->clientfd = accept(this->sockfd, (struct sockaddr*) &address, &length);

	//Check the file descriptor.
	if(SOCKET_ERROR == this->clientfd){
		std::runtime_error e("Could not create client descriptor.");
		throw(e);
	}

	//Set the non-blocking.
	if(SOCKET_ERROR == fcntl(this->clientfd, F_SETFL, O_NONBLOCK)){
		std::logic_error e("Could not block.");
		throw(e);
	}

	this->pollRequest();

	this->clientInfo.ip = address.sin_addr.s_addr;
	this->clientInfo.port = address.sin_port;

	//Log client information.
	Logger::logSection("Client Information");
	Logger::logInfo("Descriptor: " + std::to_string(clientfd));
	Logger::logInfo("IP: " + std::to_string(this->clientInfo.ip));
	Logger::logInfo("Port: " + std::to_string(this->clientInfo.port));
	Logger::endSection();

}

void SocketHandler::closeServerSocket(){
	close(this->sockfd);
}

void SocketHandler::closeClientSocket(){
	close(this->clientfd);
}

std::string SocketHandler::receiveMessage(){
	//For returning the request.
	std::string request;

	//Create a buffer for receiving segments of a client message.
	char buffer[256];
	memset(buffer, 0, sizeof(buffer));

	while(0 < read(this->clientfd, buffer, sizeof(buffer) - 1)){

		//Parses the buffer into the reqeust.
		request += std::string(buffer);

	}

	return request;

}

void SocketHandler::sendMessage(std::string message){
	if(-1 == write(this->clientfd, message.c_str(), message.size())){
		std::logic_error e("Could not write btyes.");
		throw(e);
	}
}

socketInfo SocketHandler::getClientInfo(){
	return this->clientInfo;
}

struct sockaddr_in SocketHandler::createAddress(){
	struct sockaddr_in address;
	memset(&address, 0, sizeof(address));
	return address;
}

void SocketHandler::pollRequest(){
	struct pollfd pollList[1];
	pollList[0].fd = this->clientfd;
	pollList[0].events = POLLIN;

	if(SOCKET_ERROR == poll(pollList, 1, 10000)){
		std::logic_error e("Poll has timed out.");
		throw(e);
	}

	return;
}
