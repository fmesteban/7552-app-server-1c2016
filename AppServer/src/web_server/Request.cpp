/** Include area. */
#include "Request.h"
#include <sstream>
#include <utility>
#include <map>
#include <string>


/** Loads a request from a mongoose message.
 * 	Useful when user receives requests.
 */
Request::Request(
		struct mg_connection &networkConnection,
		struct http_message &httpMessage):
	method(httpMessage.method.p, httpMessage.method.len),
	uri(httpMessage.uri.p, httpMessage.uri.len),
	body(httpMessage.body.p, httpMessage.body.len),
	networkConnection(networkConnection) {
}


/** Constructs an empty request.
 * 	Useful when user sends requests.
 */
Request::Request(struct mg_connection &networkConnection):
	networkConnection(networkConnection) {
}


/** Sets the http method (i.e. POST, GET)
 *
 */
void Request::setMethod(const std::string &method){
	this->method = method;
}


/**	Sets the http uri (without url)
 *
 */
void Request::setUri(const std::string &uri){
	this->uri = uri;
}


/** Adds a http header.
 *
 */
void Request::insertHeader(const std::string &name, const std::string &value){
	headers.insert(std::pair<std::string,std::string>(name,value));
}


/** Sets the http method (i.e. POST, GET)
 *
 */
std::string& Request::getMethod(){
	return method;
}


/**	Gets the http uri (without url)
 *
 */
std::string& Request::getUri(){
	return uri;
}


/**	Sets the http body (field data)
 *
 */
std::string& Request::getBody(){
	return body;
}


/**	Sends the current Request to its networkConnection.
 *
 */
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
