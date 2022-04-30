/*
 * StatusPage.cpp
 *
 *  Created on: Apr 18, 2022
 *      Author: mrb3271
 */

//Implementation of header file.
#include "StatusPage.h"

//Network Libraries
#include "../server/SocketHandler.h"	//For socketInfo struture.
#include "../server/Server.h"			//For receiving the server.
#include "../utilities/TimeHandler.h"	//For handling time.

//POSIX Libraries
#include "sys/sysinfo.h"	//For collecting system information.
#include "sys/utsname.h"	//For collecting kernel information.

//Standard C++ Library
#include <iomanip>	//For manipulating input and output.
#include <sstream>	//For string streams.
#include <string>	//For handling strings.
#include <cstring>	//For handling c strings.

//Macros
#define byteToMegaByte(byte) (double) byte /1048576

StatusPage::StatusPage(std::string serverName, socketInfo clientInfo) {

	//For getting kernel information.
	struct utsname kernelInfo;
	if(-1 == uname(&kernelInfo)){
		throw("Could not get kernel information.");
	}

	//For getting system information.
	struct sysinfo systemInfo;
	if(-1 == sysinfo(&systemInfo)){
		throw("Could not get system information.");
	}

	//Create the page.
	//Set the meta data of the page.
	this->setStatus(HTML_STATUS_200);
	this->setServer(serverName);
	this->setContent(HTML_CONTENT_TEXT);

	//Set the titile and header of the page.
	this->setTitle("Server Status");
	this->addHeader1("Server Status");

	//Fetch the system time and date.
	this->addParagraph("System Date: " + TimeHandler::getDate(DATE_MDY, "/"));
	this->addParagraph("Time Updated: " + TimeHandler::getTime(TIME_24HMS, ":"));

	//Get the kernal information.
	this->addHeader2("Kernel");
	this->addParagraph("Operating System: " + std::string(kernelInfo.sysname));
	this->addParagraph("Server: " + std::string(kernelInfo.nodename));
	this->addParagraph("Release: " + std::string(kernelInfo.release));
	this->addParagraph("Version: " + std::string(kernelInfo.version));
	this->addParagraph("Hardware: " + std::string(kernelInfo.machine));

	std::stringstream stream;

	//Get the system information.
	this->addHeader2("System");

	stream << std::setprecision(2) << systemInfo.uptime;
	this->addParagraph("Server Up Time: " + stream.str() + " Seconds");
	stream.str(std::string());

	stream << "Total RAM: " << std::setprecision(2) << byteToMegaByte(systemInfo.totalram) << " MB";
	this->addParagraph(stream.str());
	stream.str(std::string());

	stream << "Free RAM: " << std::setprecision(2) << byteToMegaByte(systemInfo.freeram) << " MB";
	this->addParagraph(stream.str());
	stream.str(std::string());

	stream << "Shared RAM: " << std::setprecision(2) << byteToMegaByte(systemInfo.sharedram) << " MB";
	this->addParagraph(stream.str());
	stream.str(std::string());

	stream << "Buffer RAM: " << std::setprecision(2) << byteToMegaByte(systemInfo.bufferram) << " MB";
	this->addParagraph(stream.str());
	stream.str(std::string());

	this->addParagraph("Total Swap: " + std::to_string(systemInfo.totalswap));
	this->addParagraph("Current Processes: " + std::to_string(systemInfo.procs));
	this->addParagraph("Total High: " + std::to_string(systemInfo.totalhigh));
	this->addParagraph("Free High: " + std::to_string(systemInfo.freehigh));
	this->addParagraph("Memory Unit: " + std::to_string(systemInfo.mem_unit));

	//Get the client information.
	this->addHeader2("Client");
	this->addParagraph("IP Address: " + std::to_string(clientInfo.ip));
	this->addParagraph("Port: " + std::to_string(clientInfo.port));

}

StatusPage::~StatusPage() {
	// TODO Auto-generated destructor stub
}

