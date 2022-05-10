/*
 * ProcPage.h
 *
 *  Created on: May 9, 2022
 *      Author: Michael Bloom & Andrew Juhola
 */

#ifndef PROCPAGE_H_
#define PROCPAGE_H_

//Parent class.
#include "WebPage.h"

//Standard C++ Libraries
#include <vector>	//For handling vector data structure.
#include <string>	//For handling strings.

class ProcPage: public WebPage {
	public:
		std::string url;

	public:
		ProcPage(std::string serverName, std::string url);
		virtual ~ProcPage();

	public:
		void getFileContents(std::vector<std::vector<std::string>> *contents);
};

#endif /* PROCPAGE_H_ */
