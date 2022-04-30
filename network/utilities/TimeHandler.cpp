/*
 * TimeHandler.cpp
 *
 *  Created on: Mar 28, 2022
 *      Author: Michael Bloom & Andrew Juhola
 */

//Implementation of the header file.
#include "TimeHandler.h"

//Standard C++ Libraries
#include <iostream>	//For handling input and output.
#include <string>	//For handling strings.
#include <sstream>	//For handling string streams.
#include <iomanip>	//For manipulating strings.
#include <chrono>	//For handling time.

TimeHandler::TimeHandler() {
	// TODO Auto-generated constructor stub

}

TimeHandler::~TimeHandler() {
	// TODO Auto-generated destructor stub
}

std::string TimeHandler::getDate(short format, const char *separator){

	//Get the local time and declare the time stamp.
	struct tm localTime = getLocalTime();
	std::stringstream timeStamp;

	//Check date formatting.
	switch(format){

		//Create a time stamp of day, month, year.
		case 1:
			timeStamp << std::put_time(&localTime, "%d")
			<< separator << std::put_time(&localTime, "%m")
			<< separator << std::put_time(&localTime, "%Y");
			break;

		//Create a time stamp of year, month, day.
		case 2:
			timeStamp << std::put_time(&localTime, "%Y")
			<< separator << std::put_time(&localTime, "%m")
			<< separator << std::put_time(&localTime, "%d");
			break;

		//Create a time stamp of month, day, year.
		case 0:
		default:
			timeStamp << std::put_time(&localTime, "%m")
			<< separator << std::put_time(&localTime, "%d")
			<< separator << std::put_time(&localTime, "%Y");
			break;
	}

	return timeStamp.str();
}

std::string TimeHandler::getTime(short format, const char *separator){

	//Get the local time and declare the time stamp.
	struct tm localTime = getLocalTime();
	std::stringstream timeStamp;

	//Check time formatting.
	switch(format){

		//Create a 12 hour time stamp.
		case 0:
			timeStamp << std::put_time(&localTime, "%H")
			<< separator << std::put_time(&localTime, "%M")
			<< separator << std::put_time(&localTime, "%S");
			break;

		//Create a 24 hour time stamp.
		case 1:
		default:
			timeStamp << std::put_time(&localTime, "%H")
			<< separator << std::put_time(&localTime, "%M")
			<< separator << std::put_time(&localTime, "%S");
			break;
	}

	return timeStamp.str();

}

std::string TimeHandler::getFileTime(struct timespec spec){

	//Get the local time of the file.
	struct tm localTime = convertTimeSpec(spec);

	//Create a time stamp.
	std::stringstream timeStamp;
	timeStamp << std::put_time(&localTime, "%m")
			<< "/" << std::put_time(&localTime, "%d")
			<< "/" << std::put_time(&localTime, "%Y")
			<< " " << std::put_time(&localTime, "%H")
			<< ":" << std::put_time(&localTime, "%M")
			<< ":" << std::put_time(&localTime, "%S");

	//Return the time stamp as a string.
	return timeStamp.str();

}

struct tm TimeHandler::convertTimeSpec(struct timespec spec){
	//Converts timespec to a time point.
	auto timeDuration = std::chrono::seconds(spec.tv_sec) + std::chrono::nanoseconds(spec.tv_nsec);
	std::chrono::system_clock::time_point timePoint(std::chrono::duration_cast<std::chrono::system_clock::duration>(timeDuration));

	//Creates a time based on the time point.
	auto fileTime = std::chrono::system_clock::to_time_t(timePoint);

	//Get the local time of the file.
	struct tm localTime;
	localtime_r(&fileTime, &localTime);

	//Return the time of the file.
	return localTime;
}

struct tm TimeHandler::getLocalTime(){
	//Get the current time.
	auto currentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

	//Get the local time.
	struct tm localTime;
	localtime_r(&currentTime, &localTime);

	//Return the local time.
	return localTime;
}
