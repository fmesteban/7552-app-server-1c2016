#include "Response.h"
#include <string>


/** Builds an empty Response.
 * 	After, user must call parseMessage to have a well formed response.
 * 	Useful when user receives responses.
 */
Response::Response(){
	status = UNDEFINED_STATUS;
}


/** Builds an empty Response.
 * 	Useful when user sends responses.
 */
Response::Response(httpStatus st, std::string msg){
	status = st;
	body = msg;
}


/** Extracts body and response code from a http message.
 *
 * TODO: if needed, parse needed headers, etc...*/
void Response::parseMessage(struct http_message &httpMessage){
	body = std::string(httpMessage.body.p, httpMessage.body.len);
	status = httpMessage.resp_code;
}


/** Returns a reference to the data field.
 *
 */
std::string &Response::getBody(){
	return body;
}


/** Returns response http status code.
 *
 */
httpStatus Response::getStatus(){
	return status;
}
