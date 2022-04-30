/*
 * StatusPage.h
 *
 *  Created on: Apr 18, 2022
 *      Author: Michael Bloom & Andrew Juhola
 *
 *      Page for the server status.
 *
 */

#ifndef STATUSPAGE_H_
#define STATUSPAGE_H_

//Parent Class
#include "WebPage.h"

//Network Libraries
#include "../server/SocketHandler.h"	//For the socketInfo structure.

//Network Libraries
#include "../server/Server.h"	//For the server.

class StatusPage: public WebPage {
	public:
		StatusPage(std::string serverName, socketInfo clientInfo);
		virtual ~StatusPage();
};

#endif /* STATUSPAGE_H_ */
