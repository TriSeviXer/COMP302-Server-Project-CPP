/*
 * DirectoryPage.h
 *
 *  Created on: Apr 18, 2022
 *      Author: Michael Bloom & Andrew Juhola
 *
 *     	Page for displaying server directories.
 */

#ifndef DIRECTORYPAGE_H_
#define DIRECTORYPAGE_H_

//Parent class.
#include "WebPage.h"

//POSIX Libraries
#include <sys/stat.h>	//For collecting file information.
#include <dirent.h>		//For collecting files.

//Standard C++ Libraries
#include <vector>	//For the vector data structure.
#include <string>	//For handling strings.
#include <thread>	//For handling threads.
#include <atomic>	//For atomic variables.
#include <mutex>	//For mutexes.

class DirectoryPage: public WebPage {

	protected:
		std::mutex flag;
		std::vector<std::thread> threads;
		std::string url;
		std::string path;

	public:
		DirectoryPage(std::string serverName, std::string path);
		virtual ~DirectoryPage();

	protected:

		/**
		 * Creates an absolute path.
		 * @param std::string is the path from the client.
		 * @return std::stirng is the absolute path.
		 */
		std::string getAbsolutePath(std::string path);

		/**
		 * Collects directory information.
		 * @param int is the number of directories.
		 * @param struct dirent** is the directories.
		 * @param std::vector<std::vector<std::string>> is the contents for the a table.
		 */
		void getDirectories(std::atomic<int> &directoryCount, struct dirent **directoryList, std::vector<std::vector<std::string>>& contents);

		/**
		 * Pushes to the array and makes use of mutexes.
		 * @param std::vector<std::vector<std::string>> is the array being modified.
		 * @param std::vector<std::string> is the column being pushed into the array being modified.
		 */
		void pushTo(std::vector<std::vector<std::string>> *contents, std::vector<std::string> column);

		/**
		 * Scans the directory with the given path.
		 * @param struct dirent is the list of directories.
		 * @param std::string is the path for the directory.
		 * @return int number of directories.
		 */
		int scanDirectories(struct dirent ***directoryList, std::string path);

};

#endif /* DIRECTORYPAGE_H_ */
