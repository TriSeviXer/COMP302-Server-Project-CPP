/*
 * ErrorPage.cpp
 *
 *  Created on: Apr 18, 2022
 *      Author: mrb3271
 */

#include "ErrorPage.h"

ErrorPage::ErrorPage(std::string serverName) {

	//Sets the meta data of the page.
	this->setStatus(HTML_STATUS_404);
	this->setServer(serverName);
	this->setContent(HTML_CONTENT_TEXT);

	//Sets the title and header of the page.
	this->setTitle("404: Page Not Found");
	this->addHeader1("404 - Page Not Found");
}

ErrorPage::~ErrorPage() {
	// TODO Auto-generated destructor stub
}

