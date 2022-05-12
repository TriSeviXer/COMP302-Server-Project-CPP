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
#include <thread>	//For multi threading.
#include <atomic>	//For atomic variables.
#include <mutex>	//For mutexes.

//Standard C Libraries
#include <ctime>	//For handling timespec.

DirectoryPage::DirectoryPage(std::string serverName, std::string url) : url(url){
	//For getting the directories.
	struct dirent **directoryList;
	std::atomic<int> directoryCount(0);

	//Get the absolute path.
	this->path = this->getAbsolutePath(url);
	Logger::logInfo("Absolute Path: " + this->path);

	//Scans the directory.
	directoryCount = this->scanDirectories(&directoryList, this->path);

	Logger::logInfo("Number of Directories: " + std::to_string(directoryCount));

	//Sets the meta data.
	this->setStatus(HTML_STATUS_200);
	this->setServer(serverName);
	this->setContent(HTML_CONTENT_TEXT);
	this->setStyle(CSS_TABLE);

	//Sets the title and header of the page.
	this->setTitle("Server Directories");
	this->addHeader1("Server Directories");

	//Vectors for table displaying directory information.
	std::vector<std::string> header = {"File", "Bytes", "Last Modified"};
	std::vector<std::vector<std::string>> contents;

	int threadCount = 0;

	do {

		//Creates threads to help collect directory information.
		Logger::logInfo("Creating Directory thread: " + std::to_string(threadCount));
		std::thread dirThread(&DirectoryPage::getDirectories, this, std::ref(directoryCount), std::ref(directoryList), std::ref(contents));
		threads.push_back(std::move(dirThread));
		threadCount++;

	} while(threadCount < 2); // More than 2 threads creates a segmentation fault.

	//Joins threads after completion.
	for(auto &dirThread : threads){
		Logger::logInfo("Joining thread...");
		dirThread.join();
	}

	//Creates a table for the directory contents.
	Logger::logInfo("Creating table.");
	this->addTable(header, contents);
	free(directoryList);

}

DirectoryPage::~DirectoryPage() {

}

std::string DirectoryPage::getAbsolutePath(std::string path){
	int postion = path.find('/', 1);
	path.replace(0, postion, "");
	return path;
}

void DirectoryPage::getDirectories(std::atomic<int> &directoryCount, struct dirent **directoryList, std::vector<std::vector<std::string>> &contents){

	//Struct for file information.
	struct stat stats;

	//Fetch all the directories for the user.
	while(directoryCount--){

		std::string item = directoryList[directoryCount]->d_name;

		//Creates a vector to hold multiple columns for a row.
		std::vector<std::string> column;

		//Check if a dot directory.
		if(item != "." && item != ".."){

			//Creates a link for a directory.
			if(DT_DIR == directoryList[directoryCount]->d_type){

				//Creates an address for a hyperlink.
				std::string address("/dir" + path);

				//Checks for a slash at the end of the url.
				if(PAGE_SUCCESS != path.compare(path.length() - 1, 1, "/")){
					item = '/' + item;
				}

				//Adds the item to the end of the address.
				address += item;

				//Creates the address.
				item = "<a href=\"" + address + "\">" + std::string(directoryList[directoryCount]->d_name) + "</a>";

			}

			column.push_back(item);

			//Collects the infomration for a file.
			if(PAGE_ERROR == stat((path + "/" + directoryList[directoryCount]->d_name).c_str(), &stats)){
				Logger::logWarn("Unable to collect file information for '" + std::string(directoryList[directoryCount]->d_name) + "'.");
				column.push_back("Unavailable");
				column.push_back("Unavailable");

			} else {
				column.push_back(std::to_string(stats.st_size));
				column.push_back(TimeHandler::getFileTime(stats.st_mtim));

			}
		}

		//Pushes the column to a row.
		this->pushTo(&contents, column);

		if(1 > directoryCount){
			break;
		}

	}
}

void DirectoryPage::pushTo(std::vector<std::vector<std::string>> *contents, std::vector<std::string> column){
	std::lock_guard<std::mutex> contentLock(flag);
	contents->push_back(column);

}

int DirectoryPage::scanDirectories(struct dirent ***directoryList, std::string path){
	//Scans the directory.
	int numberOfDirectories = scandir(path.c_str(), directoryList, NULL, alphasort);

	//Checks if the directory was scanned.
	if(-1 == numberOfDirectories){
		std::logic_error e("Could not scan directory.");
		throw(e);
	}

	return numberOfDirectories;

}
