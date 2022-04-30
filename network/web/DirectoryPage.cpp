/*
 * DirectoryPage.cpp
 *
 *  Created on: Apr 18, 2022
 *      Author: Michael Bloom & Andrew Juhola
 */

//Implementation of header file.
#include "DirectoryPage.h"

//Network Libraries
#include "../utilities/Logger.h"		//For logging.
#include "../utilities/TimeHandler.h"	//For handling time.

//POSIX Libraries
#include <sys/stat.h>	//For collecting file information.
#include <dirent.h>		//For collecting files.

//Standard C++ Libraries
#include <iostream>	//For handling input and output.
#include <vector>	//For the vector data structure.
#include <string>	//For handling strings.

//Standard C Libraries
#include <ctime>	//For handling timespec.

DirectoryPage::DirectoryPage(std::string serverName, std::string url) {
	struct dirent **nameList;
	int numDirectories = 0;

	std::string path = this->getAbsolutePath(url);

	//Scans the directory.
	numDirectories = scandir(path.c_str(), &nameList, NULL, alphasort);

	//Checks if the directory was scanned.
	if(-1 == numDirectories){
		throw("Could not scan directory.");
	}

	//Sets the meta data.
	this->setStatus(HTML_STATUS_200);
	this->setServer(serverName);
	this->setContent(HTML_CONTENT_TEXT);
	this->setStyle("table, th, td { border: 1px solid black; }");

	//Sets the title and header of the page.
	this->setTitle("Server Directories");
	this->addHeader1("Server Directories");

	//Vectors for table displaying directory information.
	std::vector<std::string> header = {"File", "Bytes", "Last Updated"};
	std::vector<std::vector<std::string>> contents;

	//Struct for file information.
	struct stat stats;

	//Fetch all the directories for the user.
	while(numDirectories--){
		std::string item = nameList[numDirectories]->d_name;

		//Creates a vector to hold multiple columns for a row.
		std::vector<std::string> column;

		//Check if a dot directory.
		if(item != "." && item != ".."){

			//Creates a link for a directory.
			if(DT_DIR == nameList[numDirectories]->d_type){
				item.insert(0, "<a href=\"" + url);
				item.append("/\">" + std::string(nameList[numDirectories]->d_name) + "</a>");
			}

			column.push_back(item);

			//Collects the infomration for a file.
			if(-1 == stat((path + nameList[numDirectories]->d_name).c_str(), &stats)){
				Logger::logWarn("Unable to collect file information for '" + std::string(nameList[numDirectories]->d_name) + "'.");
				column.push_back("Unavailable");
				column.push_back("Unavailable");

			} else {
				column.push_back(std::to_string(stats.st_size));
				column.push_back(TimeHandler::getFileTime(stats.st_mtim));

			}
		}

		//Pushes the column to a row.
		contents.push_back(column);

		free(nameList[numDirectories]);

		if(1 > numDirectories){
			break;
		}

	}

	this->addTable(header, contents);
	free(nameList);

}

DirectoryPage::~DirectoryPage() {

}

std::string DirectoryPage::getAbsolutePath(std::string path){
	int postion = path.find('/', 1);
	path.replace(0, postion, "");
	Logger::logInfo(path);
	return path;
}
