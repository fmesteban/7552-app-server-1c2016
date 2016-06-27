/** Include area. */
#include "RequestHandlerDislike.h"
#include "Response.h"
#include "User.h"
#include <iostream>
#include <string>


/*------------------------------------------------------------------------
 * 	Member Functions Implementations
 * ---------------------------------------------------------------------*/

/** Request handler dislike will handle the uri "/dislike".
 *
 * 	\param users Is the server users container.
 */
RequestHandlerDislike::RequestHandlerDislike(UsersContainer &users) :
users(users),
RequestHandler("/dislike") {
}


/** Parse the /dislike uri input, and saves the like from User A to B
 *  database.
 *
 *	\param request Is the request sent by client.
 */
void RequestHandlerDislike::run(Request &request){
	Log::instance()->append("Received a dislike request", Log::INFO);

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

	std::string emailSrc = root.get("emailSrc", "unavailable").asString();
	std::string emailDst = root.get("emailDst", "unavailable").asString();

	if(emailSrc == "unavailable" || emailDst == "unavailable"){
		Response response(BAD_REQUEST_STATUS, BAD_REQUEST_MSG);
		RequestHandler::sendResponse(response, request.getNetworkConnection());
		Log::instance()->append(
			"Received a BAD (incomplete) REQUEST. Rejected.",
			Log::INFO);
		return;
	}

	int idSrc = users.getID(emailSrc);
	int idDst = users.getID(emailDst);
	if (idSrc == -1 || idDst == -1){
		if(idSrc == -1){
			Log::instance()->append(
				"User with email: " + emailSrc + "was not found. Rejected.",
				Log::INFO);
		}
		else {
			Log::instance()->append(
				"User with email: " + emailDst + "was not found. Rejected.",
				Log::INFO);			
		}
		Response response(BAD_REQUEST_STATUS, BAD_REQUEST_MSG);
		RequestHandler::sendResponse(response, request.getNetworkConnection());
		return;
	}

	User *userSrc = users.getUser(idSrc);
	if (userSrc){
		Log::instance()->append(
			"User " + emailSrc + "(" + std::to_string(idSrc) + ")" + " dislikes user " + emailDst + "(" + std::to_string(idDst) + ")",
			Log::INFO);
		userSrc->dislike(idDst);
	}else{
		Response response(BAD_REQUEST_STATUS, BAD_REQUEST_MSG);
		RequestHandler::sendResponse(response, request.getNetworkConnection());
		Log::instance()->append(
			"Unavailable source user. Rejected.",
			Log::INFO);
		return;
	}

	/* Sends response to the client */
	Response response(ACCEPTED_STATUS, "{}");
	RequestHandler::sendResponse(response, request.getNetworkConnection());
}
