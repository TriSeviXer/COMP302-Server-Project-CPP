/*
 * ErrorPage.h
 *
 *  Created on: Apr 18, 2022
 *      Author: Michael Bloom & Andrew Juhola
 *
 *      Page for 404 Errors.
 *
 */

#ifndef ERRORPAGE_H_
#define ERRORPAGE_H_

#include "WebPage.h"

class ErrorPage: public WebPage {
	public:
		ErrorPage(std::string serverName);
		virtual ~ErrorPage();
};

#endif /* ERRORPAGE_H_ */
