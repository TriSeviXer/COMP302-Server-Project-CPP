/*
 * WebPage.cpp
 *
 *  Created on: Apr 18, 2022
 *      Author: Michael Bloom & Andrew Juhola
 */

//Implementation of header file.
#include "WebPage.h"

//Network Libraries
#include "ErrorPage.h"		//For error page.
#include "StatusPage.h"		//For status page.
#include "DirectoryPage.h"	//For directory page.

//Standard C++ Libraries
#include <vector>	//For vector data structure.
#include <sstream>	//For handling string streams.

WebPage::WebPage() {


}

WebPage::~WebPage() {

}

std::shared_ptr<WebPage> WebPage::createPage(int type, socketInfo info, std::string serverName, std::string path){
	std::shared_ptr<WebPage> page = nullptr;

	switch(type){
		case PAGE_404:
			page.reset(new ErrorPage(serverName));
			return page;

		case PAGE_STA:
			page.reset(new StatusPage(serverName, info));
			return page;

		case PAGE_DIR:
			page.reset(new DirectoryPage(serverName, path));
			return page;

		default:
			page.reset(new ErrorPage(serverName));
			return page;
	}

}

std::string WebPage::getWebPage(){
	std::string page = this->status + this->server + this->content +
			"\r\n <html> <head>" + this->title + "<style>" + this->style + "</style> </head> <body>" + this->body + "</body> </html> \n";
	return page;
}

WebPage* WebPage::setStatus(std::string status){
	this->status.clear();
	this->status = status + "\r\n";
	return this;
}

WebPage* WebPage::setServer(std::string server){
	this->server.clear();
	this->server = ("Server: " + server + "\r\n");
	return this;
}

WebPage* WebPage::setContent(std::string content){
	this->content.clear();
	this->content = ("Content-Type: " + content + "\r\n");
	return this;
}

WebPage* WebPage::setStyle(std::string style){
	this->style.clear();
	this->style = style;
	return this;
}

WebPage* WebPage::setBody(std::string body){
	this->body.clear();
	this->body = body;
	return this;
}

WebPage* WebPage::setTitle(std::string title){
	this->title.clear();
	this->title = "<title>" + title + "</title>";
	return this;
}

WebPage* WebPage::addStyle(std::string style){
	this->style.append(style);
	return this;
}

WebPage* WebPage::addHeader1(std::string contents){
	this->body.append("<h1>" + contents + "</h1>");
	return this;
}

WebPage* WebPage::addHeader2(std::string contents){
	this->body.append("<h2>" + contents + "</h2>");
	return this;
}

WebPage* WebPage::addParagraph(std::string contents){
	this->body.append("<p>" + contents + "</p>");
	return this;
}

WebPage* WebPage::addList(std::vector<std::string> contents){
	this->body.append("<ul>");

	std::vector<std::string>::iterator current = contents.begin();

	while(current < contents.end()){
		this->body.append("<li>" + *current + "</li>");
		current++;
	}

	this->body.append("</ul>");

	return this;
}

WebPage* WebPage::addTable(std::vector<std::string> header, std::vector<std::vector<std::string>> contents){

	std::vector<std::vector<std::string>>::iterator row = contents.begin();
	std::vector<std::string>::iterator column = header.begin();

	this->body.append("<table>");

	this->body.append("<tr>");

	//Creates a header.
	while(column < header.end()){
		this->body.append("<th>" + std::string(column->data()) + "</th>");
		column++;
	}

	this->body.append("</tr>");

	//Populates each row with data for each column.
	while(row < contents.end()){

		column = row->begin();
		this->body.append("<tr>");

		while(column < row->end()){

			this->body.append("<td>" + std::string(column->data()) + "</td>");

			column++;
		}

		this->body.append("</tr>");
		row++;

	}

	this->body.append("</table>");

	return this;
}

WebPage* WebPage::addElement(std::string element){
	this->body.append(element);
	return this;
}

WebPage* WebPage::clearBody(){
	this->body.clear();
	return this;
}
