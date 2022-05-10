/*
 * ProcPage.cpp
 *
 *  Created on: May 9, 2022
 *      Author: Michael Bloom & Andrew Juhola
 */

//Implementation of header file.
#include "ProcPage.h"

//For logging files.
#include "../utilities/Logger.h"

//POSIX Libraries
#include <sys/stat.h>	//For collecting file information.
#include <dirent.h>		//For collecting files.

//Standard C++ Libraries
#include <thread>	//For handling threads.
#include <vector>	//For handling vector data structure.
#include <string>	//For handling strings.
#include <sstream> 	//For handling string streams.
#include <fstream>	//Handling file input and output.
#include <iostream>	//For handling input and output.

ProcPage::ProcPage(std::string serverName, std::string url) : url(url) {

	//Sets the meta data.
	this->setStatus(HTML_STATUS_200);
	this->setServer(serverName);
	this->setContent(HTML_CONTENT_TEXT);
	this->setStyle(CSS_TABLE);

	//Sets the title and hader of the page.
	this->setTitle("Server Proc");

	//Vectors for the table displaying file information.
	std::vector<std::string> header = {"Property", "Data"};
	std::vector<std::vector<std::string>> contents;

	//Find the type of proc page.
	if(PAGE_SUCCESS == url.compare("/proc/crypto")){
		//Returns the proc page for crypto.
		Logger::logInfo("Retrieving crypto information.");
		this->addHeader1("Crypto");
		this->addParagraph("Lists all the ciphers used by the kernal.");
		this->getFileContents(&contents);

	} else if(PAGE_SUCCESS == url.compare("/proc/meminfo")){
		//Returns the proc page for memory.
		Logger::logInfo("Retrieving memory information.");
		this->addHeader1("MEM Info");
		this->addParagraph("Lists where all the memory is allocated.");
		this->getFileContents(&contents);

	} else if(PAGE_SUCCESS == url.compare("/proc/cpuinfo")){
		//Returns the proc page for cpu.
		Logger::logInfo("Retrieving CPU information.");
		this->addHeader1("CPU Info");
		this->addParagraph("Lists the CPU capabilities.");
		this->getFileContents(&contents);

	} else {
		//If the page is invalid, then throw an error.
		std::logic_error e("Invalid proc page.");
		throw(e);
	}

	//Gets the file contents.
	Logger::logInfo("Collecting file contents.");
	this->getFileContents(&contents);

	//Creates a table.
	Logger::logInfo("Creating table.");
	this->addTable(header, contents);

}

ProcPage::~ProcPage() {
	// TODO Auto-generated destructor stub
}

void ProcPage::getFileContents(std::vector<std::vector<std::string>> *contents){

	//Opens a file.
	std::ifstream input(url);

	//Output for an HTML element.
	std::string output;

	//Collects the contents of the file.
	while(!input.eof()){

		//Creates a vector to hold multiple columns for a row.
		std::vector<std::string> column;

		//Retrieves the property.
		std::getline(input, output, ':');
		column.push_back(output);

		//Retrieves the data
		std::getline(input, output);
		column.push_back(output);

		contents->push_back(column);

	}

	return;
}
