/** Include area. */
#include "RequestHandlerCheckToken.h"
#include "Response.h"
#include "User.h"
#include <iostream>
#include <string>


/*------------------------------------------------------------------------
 * 	Member Functions Implementations
 * ---------------------------------------------------------------------*/

/** Request handler checktoken will handle the uri "/checktoken".
 *
 * 	\param users Is the server users container.
 */
RequestHandlerCheckToken::RequestHandlerCheckToken(UsersContainer &users) :
users(users),
RequestHandler("/checktoken") {
}


/** Parse the /checktoken uri input, and responds if the user has a
 * 	valid token.
 *
 *	\param request Is the request sent by client.
 */
void RequestHandlerCheckToken::run(Request &request){
	Log::instance()->append("Received a checktoken request", Log::INFO);

	if (request.getMethod() != "POST"){
		/* some libraries send OPTIONS before POST */
		Response response(BAD_REQUEST_STATUS, BAD_REQUEST_MSG);
		RequestHandler::sendResponse(response, request.getNetworkConnection());
		Log::instance()->append("Not a POST request. Rejected.", Log::INFO);
		return;
	}

	/* Loads the request into a JSON Value object */
	Json::Value root;
	Json::Reader reader;
	bool parsingSuccessful = reader.parse(request.getBody(), root);
	if (!parsingSuccessful){
		Response response(BAD_REQUEST_STATUS, BAD_REQUEST_MSG);
		RequestHandler::sendResponse(response, request.getNetworkConnection());
		Log::instance()->append(
				"Received a BAD (malformed) REQUEST. It was not a valid JSON request. Rejected.",
				Log::INFO);
		return;
	}

	std::string userEmail = root["email"].asString();
	std::string userToken = root["token"].asString();

	int userID = users.getID(userEmail);

	if (userID == -1){
		Log::instance()->append(
				"User with email: " + userEmail + "was not found. Rejected.",
				Log::INFO);
		Response response(BAD_REQUEST_STATUS, BAD_REQUEST_MSG);
		RequestHandler::sendResponse(response, request.getNetworkConnection());
		return;
	}

	User *userPtr = users.getUser(userID);
	httpStatus responseStatus = userPtr->hasAValidToken(userToken) ?
			ACCEPTED_STATUS : FAILED_PRECONDITION_STATUS;

	/* Sends response to the client */
	Response response(responseStatus, "{}");
	RequestHandler::sendResponse(response, request.getNetworkConnection());
}
