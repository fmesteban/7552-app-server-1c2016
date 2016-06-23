/** Include area. */
#include "RequestHandlerLike.h"
#include "Response.h"
#include "User.h"
#include <iostream>
#include <string>


/*------------------------------------------------------------------------
 * 	Member Functions Implementations
 * ---------------------------------------------------------------------*/

/** Request handler like will handle the uri "/like".
 *
 * 	\param users Is the server users container.
 */
RequestHandlerLike::RequestHandlerLike(UsersContainer &users) :
users(users),
RequestHandler("/like") {
}


/** Parse the /like uri input, and saves the like from User A to B
 *  database.
 *
 *	\param request Is the request sent by client.
 */
void RequestHandlerLike::run(Request &request){
	Log::instance()->append("Received a like request", Log::INFO);

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
				"Received a BAD (malformed) REQUEST. Rejected.",
				Log::INFO);
		return;
	}

	std::string emailSrc = root.get("emailSrc", "unavailable").asString();
	std::string emailDst = root.get("emailDst", "unavailable").asString();

	if (emailSrc == "unavailable" || emailDst == "unavailable"){
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
		Response response(BAD_REQUEST_STATUS, BAD_REQUEST_MSG);
		RequestHandler::sendResponse(response, request.getNetworkConnection());
		Log::instance()->append(
				"Some user was not found. Rejected.",
				Log::INFO);
		return;
	}

	User *userSrc = users.getUser(idSrc);

	if (userSrc){
		Suggestion *suggestion = userSrc->getSuggestion(idDst);
		if(!suggestion){
			Response response(BAD_REQUEST_STATUS, BAD_REQUEST_MSG);
			RequestHandler::sendResponse(response, request.getNetworkConnection());
			Log::instance()->append(
				"Unavailable suggestion. Rejected.",
				Log::INFO);
			return;
		}
		Log::instance()->append(
			"User " + std::to_string(idSrc) +" likes user " + std::to_string(idDst),
			Log::INFO);
		suggestion->addLike(idSrc, idDst);
		if (suggestion->isMatch()){
			Log::instance()->append("It's a match.", Log::INFO);
			users.addMatch(suggestion->generateMatch());
		}
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
