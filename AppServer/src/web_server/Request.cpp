/** Include area. */
#include "Request.h"
#include <sstream>
#include <utility>
#include <map>
#include <string>


/*------------------------------------------------------------------------
 * 	Member Functions Implementations
 * ---------------------------------------------------------------------*/

/** Loads a request from a mongoose message.
 * 	Useful when user receives requests.
 *
 * 	\param networkConnection Is the mongoose network connection.
 * 	\param httpMessage Is the mongoose HTTP message.
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
 *
 * 	\param networkConnection Is the mongoose network connection.
 */
Request::Request(struct mg_connection &networkConnection):
	networkConnection(networkConnection) {
}


/** Sets the http method (i.e. POST, GET)
 *
 *	\param method Is a refference to be copied in the internal method string.
 */
void Request::setMethod(const std::string &method){
	this->method = method;
}


/**	Sets the http uri (without url)
 *
 *	\param uri Is a refference to be copied in the internal uri string.
 */
void Request::setUri(const std::string &uri){
	this->uri = uri;
}


/** Adds a http header.
 *
 *	\param name Is the key of the header.
 *	\param value Is the value of the header.
 */
void Request::insertHeader(const std::string &name, const std::string &value){
	headers.insert(std::pair<std::string,std::string>(name,value));
}


/** Gets the http method (i.e. POST, GET)
 *
 *	\return A refference to internal method string.
 */
std::string& Request::getMethod(){
	return method;
}


/**	Gets the http uri (without url)
 *
 *	\return A refference to internal uri string.
 */
std::string& Request::getUri(){
	return uri;
}


/**	Gets the http body (field data)
 *
 *	\return A refference to internal body string.
 */
std::string& Request::getBody(){
	return body;
}


/**	Sends the current Request to its networkConnection.
 *
 *	\param content Is the string to be send as body of the request.
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
