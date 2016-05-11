#include "RequestHandler.h"
#include <string>


RequestHandler::RequestHandler(const std::string _uri):
uri(_uri){
}

/** Sends an 201 OK response to \nc, appending the \extraLine
 * TODO: refactor to take status_code and text so to generalize
 * for any kind of message.
 */
void RequestHandler::sendHttpOk(struct mg_connection *nc,
		const std::string &extraLine){
	mg_printf(nc,
			"HTTP/1.1 201 OK\r\n"
			"Access-Control-Allow-Origin: *\r\n"
			"Access-Control-Allow-Headers: content-type\r\n"
			"Transfer-Encoding: chunked\r\n"
			"\r\n");

	mg_printf_http_chunk(nc, extraLine.c_str());
	mg_send_http_chunk(nc, "", 0);
}


const std::string& RequestHandler::getUri(){
	return uri;
}


RequestHandler::~RequestHandler(){ }
