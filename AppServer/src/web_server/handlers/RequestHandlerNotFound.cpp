#include "RequestHandlerNotFound.h"
#include "Response.h"
#include <string>


RequestHandlerNotFound::RequestHandlerNotFound() :
RequestHandler(""){
}


void RequestHandlerNotFound::run(Request &request){
	Response response(BAD_REQUEST_STATUS, BAD_REQUEST_MSG);
	RequestHandler::sendResponse(response, request.getNetworkConnection());
}
