/** Include area. */
#include "RequestHandlerLogin.h"
#include "Response.h"
#include <iostream>
#include <string>


/*------------------------------------------------------------------------
 * 	Member Functions Implementations
 * ---------------------------------------------------------------------*/

/** Request handler login will handle the uri "/login".
 *
 * 	\param users Is the server users container.
 */
RequestHandlerLogin::RequestHandlerLogin(UsersContainer &users) :
users(users),
RequestHandler("/login") {
}

/** Should send the data of the user to the shared server. This should return
 *  all the fields of the user.
 *
 *	\param request Is the request sent by client.
 */
void RequestHandlerLogin::run(Request &request){
	Log::instance()->append("Received a login request", Log::INFO);

	if (request.getMethod() != "POST"){
		/* some libraries send OPTIONS before POST */
		Response response(BAD_REQUEST_STATUS, BAD_REQUEST_MSG);
		RequestHandler::sendResponse(response, request.getNetworkConnection());
		Log::instance()->append("Not a POST request. Rejected.", Log::INFO);
		return;
	}

	/* Loads body parameters */
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

	std::string email = root.get("email", "unavailable").asString();
	std::string password = root.get("password", "unavailable").asString();

	if(email == "unavailable" || password == "unavailable"){
		Response response(BAD_REQUEST_STATUS, BAD_REQUEST_MSG);
		RequestHandler::sendResponse(response, request.getNetworkConnection());
		Log::instance()->append(
				"Received a BAD (incomplete) REQUEST. Some of the fields were missing. Rejected.",
				Log::INFO);
		return;		
	}

	/* Gets the pre-existent user from users container */
	//TODO: APPEND THE TOKEN TO USER STRING!!!!
	std::string userAsString = users.login(email);
	int status = ACCEPTED_STATUS;

	if (userAsString == ""){
		Log::instance()->append(
				"User with email " + email + " was not found.", Log::ERROR);
		status = 500;
	}

	/* Generates a token and appends it to response */
	Json::Value rootResponse;
	Json::Reader readerResponse;
	readerResponse.parse(userAsString, rootResponse);
	rootResponse["token"] = users.getUser(users.getID(email))->generateToken();

	/* Sends response to the client containing its data */
	Response response(status, rootResponse.toStyledString());
	RequestHandler::sendResponse(response, request.getNetworkConnection());
}
