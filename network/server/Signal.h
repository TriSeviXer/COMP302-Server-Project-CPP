/*
 * Signal.h
 *
 *  Created on: Apr 19, 2022
 *      Author: Michael Bloom & Andrew Juhola
 */

#ifndef SIGNAL_H_
#define SIGNAL_H_

class Signal {
	//Variables and constants.
	private:
		static bool isRunning;

	//Constructors and destructors.
	public:
		Signal();
		virtual ~Signal();

	//Signal functions.
	public:

		/**
		 * Boolean for if the server is running.
		 * @return is the running state for the server.
		 */
		static bool getIsRunning();

		/**
		 * Signal for exiting the server.
		 * @param int is the signal given.
		 */
		static void signalExit(int signal);

		/**
		 * Adds a signal to the server.
		 * @param void (int) is a signal function.
		 */
		static void addSignal(void signalFunction(int));
};

#endif /* SIGNAL_H_ */
