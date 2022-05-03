/*
 * Signal.cpp
 *
 *  Created on: Apr 19, 2022
 *      Author: mrb3271
 */

#include "Signal.h"

//Network Libraries
#include "../utilities/Logger.h"

//POSIX Libraries
#include <signal.h>
#include <unistd.h>

//Standard C Libraries
#include <cstring>	//For handling c strings.

//Macros.
#define SIG_ERROR -1	//For handling POSIX errors.

bool Signal::isRunning = true;

bool Signal::getIsRunning(){
	return isRunning;
}

void Signal::signalExit(int signal){
	isRunning = false;
}

void Signal::addSignal(void signalFunction(int)){
	try {

		//Creates a sigaction struct and sets the memory locations to 0.
		struct sigaction signalAction;
		memset(&signalAction, 0, sizeof(signalAction));

		//Sets the handler of the signal action.
		signalAction.sa_handler = signalFunction;
		if(SIG_ERROR == sigemptyset(&signalAction.sa_mask)){
			std::logic_error e("Could not clear the signal set.");
			throw(e);
		}

		//Checks if the signal function was assigned.
		if(SIG_ERROR == sigaction(SIGINT, &signalAction, NULL)){
			std::logic_error e("Could not create a signal action.");
			throw(e);
		}

	} catch(const char *message){
		Logger::logError(message);
	}
}
