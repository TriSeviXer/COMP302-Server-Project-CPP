/*
 * WebPage.h
 *
 *  Created on: Apr 18, 2022
 *      Author: Michael Bloom & Andrew Juhola
 *
 *      A small framework for building pages. This is intended
 *      to be extended to construct custom pages.
 *
 */

#ifndef WEBPAGE_H_
#define WEBPAGE_H_

//Network Libraries
#include "../server/SocketHandler.h"	//For socketInfo structure.

//Standard C++ Libraries
#include <vector>	//For vector data structure.
#include <memory>	//For handling memory.
#include <string>	//For handling string.
#include <sstream>	//For string streams.

//Macros for page status.
#define HTML_STATUS_200 "HTTP/1.1 200 OK"			//200 Status
#define HTML_STATUS_404 "HTTP/1.1 404 Not Found"	//404 Status

#define HTML_SERVER "Server: "						//Server Name command.
#define HTML_CONTENT "Content-Type: "				//Content-type command.

#define HTML_CONTENT_TEXT "text/html"				//Content-type text.

//Macros for page styles.
#define CSS_TABLE "table, th, td { border: 1px solid black; }"	//Style for tables.

//Macros for page types.
#define PAGE_404 -1	//For 404 error pages.
#define PAGE_STA 0	//For status pages.
#define PAGE_DIR 1	//For directory pages.
#define PAGE_PRO 2	//For proc pages.

//Macros for success and errors
#define PAGE_SUCCESS 0	//Handles successes.
#define PAGE_ERROR -1	//Handles errors.

class WebPage {

	private:
		std::string status;
		std::string server;
		std::string content;
		std::string style;
		std::string title;
		std::string body;

	//Constructor and destructor.
	public:
		WebPage();
		virtual ~WebPage();

	public:

		/**
		 * Creates a page.
		 * @param int type is the page type.
		 * @param socketInfo is the client info.
		 * @param std::string is the server name.
		 * @param std::string is the request path.
		 * @return std::shared_ptr<WebPage> is the page returned.
		 */
		static std::shared_ptr<WebPage> createPage(int type, socketInfo info, std::string serverName, std::string path);

		/**
		 * Retrieves the web page.
		 * @return is the web page.
		 */
		std::string getWebPage();

	protected:

		/**
		 * Sets the status of the webpage.
		 * @param std::string is the status of the web page.
		 * @return is the web page.
		 */
		WebPage* setStatus(std::string status);

		/**
		 * Sets the server name.
		 * @param std::string is the name of the server giveing the page.
		 * @return is the web page.
		 */
		WebPage* setServer(std::string server);

		/**
		 * Sets the content type.
		 * @param std::string is the contents type of the page.
		 * @return is the web page.
		 */
		WebPage* setContent(std::string type);


		/**
		 * Sets the style of the page.
		 * @param std::string is the style for the page.
		 * @return is the web page.
		 */
		WebPage* setStyle(std::string style);

		/**
		 * Sets the title of the page.
		 * @param std::string is the title of the page.
		 * @return is the web page.
		 */
		WebPage* setTitle(std::string title);

		/**
		 * Sets the body of the page.
		 * @param std::string is the contents for the body of the HTML file.
		 * @return is the web page.
		 */
		WebPage* setBody(std::string body);

		/**
		 * Sets the style of the page.
		 * @param std::string is the style for the page.
		 * @return is the web page.
		 */
		WebPage* addStyle(std::string style);

		/**
		 * Adds a header element to the page.
		 * @param std::string is the header contents.
		 * @return is the web page.
		 */
		WebPage* addHeader1(std::string contents);

		/**
		 * Adds a header element to the page.
		 * @param std::string is the header contents.
		 * @return is the web page.
		 */
		WebPage* addHeader2(std::string contents);

		/**
		 * Adds a paragraph element to the page.
		 * @param std::string is the paragraph contents.
		 * @return is the web page.
		 */
		WebPage* addParagraph(std::string contents);

		/**
		 * Adds a list element to the page.
		 * @param std::vector<std::string> is the items being listed.
		 * @return is the web page.
		 */
		WebPage* addList(std::vector<std::string> contents);

		/**
		 * Adds a table element to the page.
		 * @param std::vector<std::string>> is the header of the table.
		 * @param std::vector<std::vector<std::string>> is the rows and columns of the table.
		 * @return is the web page.
		 */
		WebPage* addTable(std::vector<std::string> header, std::vector<std::vector<std::string>> contents);

		/**
		 * Adds an element to the page.
		 * @param std::string is a custom html element.
		 * @return is the web page.
		 */
		WebPage* addElement(std::string element);

		/**
		 * Clears the body contents.
		 * @return is the web page.
		 */
		WebPage* clearBody();
};

#endif /* WEBPAGE_H_ */
