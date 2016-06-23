/** Include area. */
#include "RequestHandlerNotFound.h"
#include "Response.h"
#include <string>


/*------------------------------------------------------------------------
 * 	Member Functions Implementations
 * ---------------------------------------------------------------------*/

/** Request handler not found will handle every uris unhandled by others.
 *
 */
RequestHandlerNotFound::RequestHandlerNotFound() :
RequestHandler(""){
}


/** Sends an HTTP 404 response.
 *
 *  \param request Is the request to be responded with 404 error.
 */
void RequestHandlerNotFound::run(Request &request){
	Response response(BAD_REQUEST_STATUS, BAD_REQUEST_MSG);
	RequestHandler::sendResponse(response, request.getNetworkConnection());
}
