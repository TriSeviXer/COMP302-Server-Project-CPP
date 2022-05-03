/*
 * Main.cpp
 *
 *  Created on: Apr 18, 2022
 *      Author: Michael Bloom & Andrew Juhola
 */

//Network Libraries
#include "../network/server/Server.h"			//For running the server.
#include "../network/utilities/Logger.h"		//For handling logs.
#include "../network/utilities/ArgHandler.h"	//For handling arguments.

//Standard C++ Libraries
#include <memory>	//For handling memory.

//Standard C Libraries
#include <cerrno>	//For handling errnos.

int main(int argc, char **argv) {
	try{
		//Bind a file to the log.
		Logger::bindLog();

		//Create an argument handler for handling arguments given to the program.
		std::shared_ptr<ArgHandler> argHandler(new ArgHandler(argc, argv));

		//Create the actual server.
		std::shared_ptr<Server> server(new Server());
		server->setName(argHandler->nextString())->setPort(argHandler->nextInt())->setBacklog(argHandler->nextInt())->run();

		//Close the log when finished.
		Logger::closeLog();

	} catch(std::exception &e){
		Logger::logError(errno, &e, "The program ran into a problem.");
		Logger::logError("Force exiting the program.");
		Logger::closeLog();
		return -1;
	}

	return 0;
}
