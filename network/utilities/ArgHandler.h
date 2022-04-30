/*
 * ArgHandler.h
 *
 *  Created on: Apr 26, 2022
 *      Author: Michael Bloom & Andrew Juhola
 */

#ifndef ARGHANDLER_H_
#define ARGHANDLER_H_

//Standard C++ Libraries
#include <string>	//For handling strings.

class ArgHandler {

	//Variables and Constants
	private:
		const char **ARGV;
		const int ARGC;
		int current;

	//Constructors and Destructors
	public:

		/**
		 * Creates an ArgHandler instance.
		 * @param int argc is the number of arguments given to the program.
		 * @param char **argv is the arguments list given to the program.
		 */
		ArgHandler(int argc, char **argv);

		/**
		 * Destructor for ArgHandler.
		 */
		virtual ~ArgHandler();

	//Functions.
	public:

		/**
		 * Calls for the next argument as an int.
		 * @return int argument.
		 */
		int nextInt();

		/**
		 * Calls for the next argument as a string.
		 * @return std::string argument.
		 */
		std::string nextString();
};

#endif /* ARGHANDLER_H_ */
