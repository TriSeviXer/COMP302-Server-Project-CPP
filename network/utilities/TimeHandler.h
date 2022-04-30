/*
 * TimeHandler.h
 *
 *  Created on: Mar 28, 2022
 *      Author: Michael Bloom & Andrew Juhola
 *
 *      Handles time.
 *
 */

#ifndef TIMEHANDLER_H_
#define TIMEHANDLER_H_

//Standard C++ Libraries
#include <string>	//For handling strings.
#include <chrono>	//For handling time.

//Macros for time and date formatting.
#define DATE_MDY 0		//Month, Day, Year
#define DATE_DMY 1		//Day, Month, Year
#define DATE_YMD 2		//Year, Month, Day
#define TIME_12HMS 0	//12 Hour Clock
#define TIME_24HMS 1	//24 Hour Clock

class TimeHandler {

	//Constructors and destructors.
	public:
		TimeHandler();
		virtual ~TimeHandler();

	//Functions for time.
	public:

		/**
		 * Gets the current date.
		 * @param short is the date format.
		 * @param const char is the separator for each time unit.
		 * @return std::string is the date.
		 */
		static std::string getDate(short format, const char *separator);

		/**
		 * Gets the current time.
		 * @param short is the time format.
		 * @param const char is the separator for each time unit.
		 * @return std::string is the time.
		 */
		static std::string getTime(short format, const char *separator);

		/**
		 * Get the time for a file.
		 * @param struct timespec is the time information.
		 * @param std::string is the time from the file.
		 */
		static std::string getFileTime(struct timespec spec);

	private:

		/**
		 * Converts a timespec to a struct tm.
		 * @param struct timespec spec is the time information.
		 * @return struct tm is the converted time information.
		 */
		static struct tm convertTimeSpec(struct timespec spec);

		/**
		 * Gets the local time.
		 * @return struct tm is the time information.
		 */
		static struct tm getLocalTime();
};

#endif /* TIMEHANDLER_H_ */
