/*
 * Logger.cpp
 *
 *  Created on: Mar 28, 2022
 *      Author: Michael Bloom & Andrew Juhola
 */

//Implementation of header file.
#include "Logger.h"

//Custom Classes
#include "TimeHandler.h"

//Standard C++ Libraries
#include <string>	//For handling strings.
#include <sstream>	//For handling string streams.
#include <fstream>	//For handling file input and output.
#include <iostream>	//For handling input and output.
#include <cerrno>	//For handling errnos.
#include <cstring>	//For handling c strings.

//Macros
#define TYPE_ERR "ERROR"	//Log type error.
#define TYPE_INF "INFO"		//Log type info.
#define TYPE_WAR "WARN"		//Log type warning.

#define markSection(stream, section) if(isSection) stream << "[" << section << "]";		//Checks if section is being marked.
#define sendLog(file, stream) if(file.is_open()) file << stream.str() << std::endl;		//Sends the stream to a file.

//Variables and constants.
std::ofstream Logger::logFile;
std::string Logger::section;
bool Logger::isSection;

void Logger::bindLog(){

	//Create a file name.
	std::string file = TimeHandler::getDate(DATE_YMD, "-") + "-" + TimeHandler::getTime(TIME_24HMS, "-") + ".txt";

	//Opens the log file.
	bindLog(file.c_str());

	return;
}

void Logger::bindLog(const char *file){

	//Check if file is open.
	if(!logFile.is_open()){
		logFile.open(file);
	}

	return;
}

void Logger::logSection(std::string section){
	Logger::section = section;
	isSection = true;
	return;
}

void Logger::endSection(){
	isSection = false;
	return;
}

void Logger::logInfo(std::string message){

	//Creates a stream and gets the current time.
	std::stringstream stream;
	stream << getTimeStamp(TYPE_INF);

	//Marks down a section if applicable.
	markSection(stream, section);

	stream << message;

	//Sends the stream to the console.
	std::cout << stream.str() << std::endl;
	std::flush(std::cout);

	//Sends the stream to the log file.
	sendLog(logFile, stream);

	return;
}

void Logger::logWarn(std::string message){

	//Creates a stream and gets the current time.
	std::stringstream stream;
	stream << getTimeStamp(TYPE_WAR);

	//Marks down a section if applicable.
	markSection(stream, section);

	stream << message;

	//Sends the stream to the console.
	std::cerr << stream.str() << std::endl;
	std::flush(std::cerr);

	//Sends the stream to the log file.
	sendLog(logFile, stream);

	return;
}

void Logger::logError(std::string message){

	//Creates a stream and gets the current time.
	std::stringstream stream;
	stream << getTimeStamp(TYPE_ERR);

	//Marks down a section if applicable.
	markSection(stream, section);

	stream << message;

	//Sends the stream to the console.
	std::cerr << stream.str() << std::endl;
	std::flush(std::cerr);

	//Sends the stream to the log file.
	sendLog(logFile, stream);

	return;
}

void Logger::logError(int err, std::string message){

	//Creates a stream and gets the current time.
	std::stringstream stream;
	stream << getTimeStamp(TYPE_ERR);

	//Marks down a section if applicable.
	markSection(stream, section);

	//Constructs a log message.
	stream << std::strerror(err) << ". " << message;

	//Sends the stream to the console.
	std::cerr << stream.str() << std::endl;
	std::flush(std::cerr);

	//Sends the stream to the log file.
	sendLog(logFile, stream);

	return;
}

void Logger::logError(std::exception *exception, std::string message){

	//Creates a stream and get the current time.
	std::stringstream stream;
	stream << getTimeStamp(TYPE_ERR);

	//Marks down a section if applicable.
	markSection(stream, section);

	//Constructs a log message.
	stream << exception->what() << ". " << message;

	//Sends the stream to the console.
	std::cerr << stream.str() << std::endl;
	std::flush(std::cerr);

	//Sends the stream to the log file.
	sendLog(logFile, stream);

	return;
}

void Logger::logError(int err, std::exception exception, std::string message){

	//Creates a stream and get the current time.
	std::stringstream stream;
	stream << getTimeStamp(TYPE_ERR);

	//Marks down a section applicable.
	markSection(stream, section);

	//Constrcuts a log message.
	stream << std::strerror(err) << ". " << exception.what() << ". " << message;

	//Sends the stream to the console.
	std::cerr << stream.str() << std::endl;
	std::flush(std::cerr);

	//Sends the stream to the log file.
	sendLog(logFile, stream);

	return;
}

void Logger::closeLog(){
	//Check if file is open.
	if(logFile.is_open()){
		logFile.close();
	}

	return;
}

std::string Logger::getTimeStamp(std::string logType){
	std::string value =  "[" + TimeHandler::getDate(DATE_MDY, ":") + " " + TimeHandler::getTime(TIME_24HMS, ":") + " " + logType + "]";
	return value;
}
