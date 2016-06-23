#include "RequestHandler.h"
#include <string>


RequestHandler::RequestHandler(const std::string _uri):
uri(_uri){
}

/** Sends a Response to a network connection.
 *
 */
void RequestHandler::sendResponse(Response &r, struct mg_connection *nc){
	Log::instance()->append("Sending response to client's request.", Log::INFO);
	std::stringstream ss;
	ss << "HTTP/1.1 " << r.getStatus() << " OK\r\n";
	ss << "Access-Control-Allow-Origin: *\r\n";
	ss << "Access-Control-Allow-Headers: content-type\r\n";
	ss << "Transfer-Encoding: chunked\r\n";
	ss << "\r\n";
	mg_printf(nc, "%s", ss.str().c_str());
	mg_printf_http_chunk(nc, r.getBody().c_str());
	mg_send_http_chunk(nc, "", 0);
}

/** Returns Request uri. Requests handlers who inherit from it class,
 *  must handle a specific uri.
 */
const std::string& RequestHandler::getUri(){
	return uri;
}


RequestHandler::~RequestHandler(){ }
