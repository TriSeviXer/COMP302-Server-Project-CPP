/*
 * Server.cpp
 *
 *  Created on: Mar 28, 2022
 *      Author: Michael Bloom & Andrew Juhola
 */

//Header implementation.
#include "Server.h"

//Network Libraries
#include "SocketHandler.h"			//For handling sockets.
#include "./Signal.h"				//For handling signals.
#include "../utilities/Logger.h"	//For logging.
#include "../web/WebPage.h"			//For web pages.
#include "../web/ErrorPage.h"		//For error pages.
#include "../web/StatusPage.h"		//For status pages.
#include "../web/DirectoryPage.h"	//For directories pages.

//POSIX Libraries
#include "netinet/in.h"		//For retrieving ip addresses.
#include "sys/socket.h"		//For the listener.
#include "unistd.h"			//For reading and writeing server messages.
#include "fcntl.h"			//For nonblocking.
#include "poll.h"			//For polling messages.
#include "dirent.h"

//Standard C++ Libraries
#include <memory>	//For memory handling.
#include <string>	//For handling strings.

//Standard C Libraries
#include <cstring>	//For handling memset.

Server::Server() : serverName("Server"), domain(AF_INET), type(SOCK_STREAM), portNumber(2000), backlog(5) {

}

Server::~Server() {

}

void Server::run(){

	//Log server properties.
	Logger::logInfo("Running server.");
	Logger::logSection("Server Properties");
	Logger::logInfo("Server Name: " + this->serverName);
	Logger::logInfo("Port Number: " + std::to_string(this->portNumber));
	Logger::endSection();

	//Create a socket handler.
	Logger::logInfo("Initializing socket handler.");
	std::unique_ptr<SocketHandler> socketHandler(new SocketHandler());

	//Open server socket.
	Logger::logInfo("Opening server socket.");
	socketHandler->createServerSocket(domain, type, portNumber, backlog);

	//Add signals.
	Logger::logInfo("Creating signals.");
	Signal::addSignal(Signal::signalExit);

	while(Signal::getIsRunning()){

		//Create struct for collecting socket info.
		socketInfo clientInfo;

		//Receive client connection.
		Logger::logInfo("Getting connection to client.");
		socketHandler->createClientSocket();

		try{
			//Receive client message.
			Logger::logInfo("Getting client message...");
			std::string clientMessage = socketHandler->receiveMessage();

			//Handle client message.
			Logger::logInfo("Handling request.");
			std::string serverMessage = this->processMessage(socketHandler->getClientInfo(), clientMessage);

			//Send message back to client.
			Logger::logInfo("Sending message to client.");
			socketHandler->sendMessage(serverMessage);

			//Close the client when finished.
			Logger::logInfo("Closing connection to client.");
			socketHandler->closeClientSocket();

		} catch(std::exception &e){
			Logger::logWarn("There was a problem processing the client request.");
			Logger::logWarn(e.what());
		}

	}

	//Close the server when finished.
	Logger::logInfo("Closing server socket.");
	socketHandler->closeServerSocket();

}

Server* Server::setName(std::string name){
	this->serverName = name;
	return this;
}

Server* Server::setPort(int portNumber){
	this->portNumber = portNumber;
	return this;
}

Server* Server::setBacklog(int backlog){
	this->backlog = backlog;
	return this;
}

std::string Server::processMessage(socketInfo clientInfo, std::string message){
	try{

		//Takes the message from the client.
		std::stringstream userMessage(message);
		std::string request, url;
		userMessage >> request >> url;

		//Logs the message from the user.
		Logger::logSection("User Message");
		Logger::logInfo("Request: " + request);
		Logger::logInfo("Url: " + url);
		Logger::endSection();

		//Checks if client sent a valid command.
		if(SERVER_SUCCESS == request.compare("GET")){

			//Checks for the type of page.
			if(SERVER_SUCCESS == url.compare("/status") || SERVER_SUCCESS == url.compare("/status/")){
				//Returns a status page.
				Logger::logInfo("Sending server status to client.");
				std::shared_ptr<WebPage> page = WebPage::createPage(PAGE_STA, clientInfo, serverName, url);
				return page->getWebPage();

			} else if(SERVER_SUCCESS == url.compare(0, 5, "/dir/")){
				//Returns a directories page.
				Logger::logInfo("Sending server directory to client.");
				std::shared_ptr<WebPage> page = WebPage::createPage(PAGE_DIR, clientInfo, serverName, url);
				return page->getWebPage();

			} else {
				//Returns a 404 error page.
				Logger::logInfo("Could not find page requested by client. Sending 404 error to client.");
				std::shared_ptr<WebPage> page = WebPage::createPage(PAGE_404, clientInfo, serverName, url);
				return page->getWebPage();

			}

		}

		//Returns a blank string if the request was invalid.
		return "";

	} catch(std::exception &e){

		Logger::logWarn(e.what());
		Logger::logWarn("Unknown problem sending a page. Sending 404 error page instead.");

		std::shared_ptr<ErrorPage> page(new ErrorPage(serverName));
		return page->getWebPage();

	}

}
