/** Include area. */
#include "Response.h"
#include <string>


/*------------------------------------------------------------------------
 * 	Member Functions Implementations
 * ---------------------------------------------------------------------*/

/** Builds an empty Response.
 * 	After, user must call parseMessage to have a well formed response.
 * 	Useful when user receives responses.
 */
Response::Response(){
	status = UNDEFINED_STATUS;
}


/** Builds an empty Response.
 * 	Useful when user sends responses.
 *
 * 	\param st Is the status of the created response.
 * 	\param msg Is the body of the created response.
 */
Response::Response(httpStatus st, std::string msg){
	status = st;
	body = msg;
}


/** Extracts body and response code from a http message.
 *
 *	\param httpMessage Mongoose HTTP message.
 */
void Response::parseMessage(struct http_message &httpMessage){
	body = std::string(httpMessage.body.p, httpMessage.body.len);
	status = httpMessage.resp_code;
}


/** Returns a reference to the data field.
 *
 *	\return A refference to the internal body string.
 */
std::string &Response::getBody(){
	return body;
}


/** Returns response http status code.
 *
 *	\return the http status code.
 */
httpStatus Response::getStatus(){
	return status;
}
