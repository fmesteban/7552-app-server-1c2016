/** Include area. */
#include "RequestHandler.h"
#include <string>


/*------------------------------------------------------------------------
 * 	Member Functions Implementations
 * ---------------------------------------------------------------------*/

/** Request handler generic constructor.
 *
 *	\param uri Is the uri what will be handled by the current handler.
 */
RequestHandler::RequestHandler(const std::string _uri):
uri(_uri){
}


/** Sends a Response to a network connection.
 *
 *	\param r Is the response to be sent.
 *	\param nc Is the mongoose network connection by where the
 *	response will be sent.
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
 *
 *  \return The uri as a string refference.
 */
const std::string& RequestHandler::getUri(){
	return uri;
}


RequestHandler::~RequestHandler(){ }
