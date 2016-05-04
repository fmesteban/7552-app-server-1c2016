#include "Request.h"
#include <sstream>
#include <utility>
#include <map>
#include <string>

Request::Request(
		struct mg_connection &networkConnection,
		struct http_message &httpMessage):
	uri(httpMessage.uri.p, httpMessage.uri.len),
	body(httpMessage.body.p, httpMessage.body.len),
	networkConnection(networkConnection) {
}


Request::Request(struct mg_connection &networkConnection):
	networkConnection(networkConnection) {
}


void Request::setMethod(const std::string &method){
	this->method = method;
}


void Request::setUri(const std::string &uri){
	this->uri = uri;
}


void Request::insertHeader(const std::string &name, const std::string &value){
	headers.insert(std::pair<std::string,std::string>(name,value));
}


std::string& Request::getUri(){
	return uri;
}


std::string& Request::getBody(){
	return body;
}


void Request::send(const std::string &content){
	std::stringstream ss;
	ss << method << " " << uri << " HTTP/1.1\r\n";

	std::map<std::string, std::string>::iterator header = headers.begin();
	for(; header != headers.end(); ++header)
		ss << header->first << ": " << header->second << "\r\n";

	if(content.length() > 0)
		ss << "Content-Length: " << content.length() << "\r\n\r\n" <<
				content;

	ss << "\r\n";

	mg_printf(&networkConnection, "%s", ss.str().c_str());
}
