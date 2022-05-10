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
#include "unistd.h"			//For reading and writeing server messages.

//Standard C++ Libraries
#include <memory>	//For memory handling.
#include <thread>	//For multi threading.
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

	//Creates a socket handler.
	Logger::logInfo("Createing a socket handler");
	std::unique_ptr<SocketHandler> serverSocket(new SocketHandler);

	//Open server socket.
	Logger::logInfo("Opening server socket.");
	serverSocket->createServerSocket(domain, type, portNumber, backlog);

	//Add signals.
	Logger::logInfo("Creating signals.");
	Signal::addSignal(Signal::signalExit);

	while(Signal::getIsRunning()){

		//Receive client connection.
		Logger::logInfo("Getting connection to client.");
		std::shared_ptr<SocketHandler> clientSocket = serverSocket->createClientSocket();

		Logger::logInfo("Sending connection to thread.");
		std::thread clientThread(&Server::processClient, this, std::move(clientSocket));
		clientThread.detach();

	}

	//Close the server when finished.
	Logger::logInfo("Closing server socket.");
	serverSocket->closeSocket();

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

void Server::processClient(std::shared_ptr<SocketHandler> socketHandler){
	try{

		//std::this_thread::sleep_for(std::chrono::seconds(15));

		//Receive client message.
		Logger::logInfo("Getting client message...");
		std::string clientMessage = socketHandler->receiveMessage();

		//Handle client message.
		Logger::logInfo("Handling request.");
		std::string serverMessage = this->processMessage(socketHandler->getSocketInfo(), clientMessage);

		//Send message back to client.
		Logger::logInfo("Sending message to client.");
		socketHandler->sendMessage(serverMessage);

		//Close the client when finished.
		Logger::logInfo("Closing connection to client.");
		socketHandler->closeSocket();

	} catch(std::exception &e){
		Logger::logWarn("There was a problem processing the client request.");
		Logger::logWarn(e.what());
	}
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
				auto page = WebPage::createPage(PAGE_STA, clientInfo, serverName, url);
				return page->getWebPage();

			} else if(SERVER_SUCCESS == url.compare(0, 5, "/dir/")){
				//Returns a directories page.
				Logger::logInfo("Sending server directory to client.");
				auto page = WebPage::createPage(PAGE_DIR, clientInfo, serverName, url);
				return page->getWebPage();

			} else if(SERVER_SUCCESS == url.compare(0, 6, "/proc/")){
				//Returns a proc page.
				Logger::logInfo("Sending server proc page to client");
				auto page = WebPage::createPage(PAGE_PRO, clientInfo, serverName, url);
				return page->getWebPage();

			} else {
				//Returns a 404 error page.
				Logger::logInfo("Could not find page requested by client. Sending 404 error to client.");
				auto page = WebPage::createPage(PAGE_404, clientInfo, serverName, url);
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
