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

//Standard C++ Libraries
#include <string>	//For handling strings.

class DirectoryPage: public WebPage {
	public:
		DirectoryPage(std::string serverName, std::string path);
		virtual ~DirectoryPage();
	private:

		/**
		 * Creates an absolute path.
		 * @param std::string is the path from the client.
		 * @return std::stirng is the absolute path.
		 */
		std::string getAbsolutePath(std::string path);

};

#endif /* DIRECTORYPAGE_H_ */
