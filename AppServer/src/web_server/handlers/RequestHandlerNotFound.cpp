#include "RequestHandlerNotFound.h"
#include "Response.h"
#include <string>


RequestHandlerNotFound::RequestHandlerNotFound() :
RequestHandler(""){
}


/** Sends an HTTP 404 response.
 */
void RequestHandlerNotFound::run(Request &request){
	Response response(BAD_REQUEST_STATUS, BAD_REQUEST_MSG);
	RequestHandler::sendResponse(response, request.getNetworkConnection());
}
