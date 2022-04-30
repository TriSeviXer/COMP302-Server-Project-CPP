/*
 * ArgHandler.cpp
 *
 *  Created on: Apr 26, 2022
 *      Author: mrb3271
 */

#include "ArgHandler.h"

//Standard C++ Libraries
#include <regex>	//For checking input.
#include <string>	//For handling strings.

//Macros
#define EXCEPTION_MSG_NO_ARG "Argument could not be found."

ArgHandler::ArgHandler(int argc, char **argv) : ARGV((const char**) argv), ARGC(argc) {
	this->current = 0;
}

ArgHandler::~ArgHandler() {

}

int ArgHandler::nextInt(){
	++this->current;

	if(!(this->current < ARGC)){
		std::logic_error e(EXCEPTION_MSG_NO_ARG);
		throw(e);
	}

	if(!std::regex_match(ARGV[current], std::regex("^[+-]?[1-9][0-9]*|0$"))){
		std::logic_error e("Invalid argument. Argument needs a type of int.");
		throw(e);
	}

	return std::stoi(ARGV[current]);

}

std::string ArgHandler::nextString(){
	++this->current;

	if(!(this->current < ARGC)){
		std::logic_error e(EXCEPTION_MSG_NO_ARG);
		throw(e);
	}

	return ARGV[current];

}
