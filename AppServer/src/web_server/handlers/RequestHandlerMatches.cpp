/** Include area. */
#include "RequestHandlerMatches.h"
#include "Response.h"
#include "User.h"
#include <iostream>
#include <string>
#include <map>


/*------------------------------------------------------------------------
 * 	Member Functions Implementations
 * ---------------------------------------------------------------------*/

/** Request handler matches will handle the uri "/getmatches".
 *
 * 	\param users Is the server users container.
 */
RequestHandlerMatches::RequestHandlerMatches(UsersContainer &users) :
users(users),
RequestHandler("/getmatches") {
}

/** Parse the /getmatches uri input, and saves it in the app-server
 *  database.
 *
 *	\param request Is the request sent by client.
 */
void RequestHandlerMatches::run(Request &request){
	Log::instance()->append("Received a get matches request", Log::INFO);

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
			"Received a BAD (malformed) REQUEST. "
			"It was not a valid JSON request. Rejected.",
			Log::INFO);
		return;
	}

	std::string email = root.get("email", "unavailable").asString();

	if(email == "unavailable"){
		Response response(BAD_REQUEST_STATUS, BAD_REQUEST_MSG);
		RequestHandler::sendResponse(response, request.getNetworkConnection());
		Log::instance()->append(
			"Received a BAD (incomplete) REQUEST. Rejected.",
			Log::INFO);
		return;
	}

	int userID = users.getID(email);
	if (userID == -1){
		Response response(SERVER_ERROR_STATUS, SERVER_ERROR_MSG);
		RequestHandler::sendResponse(response, request.getNetworkConnection());
		Log::instance()->append(
			"User with email: " + email + " not found.",
			Log::ERROR);
		return;
	}
	std::map<int, Match*> &matches = users.getUser(userID)->getMatches();

	std::string result;
	if (matches.size() == 0){
		result = "{\"matches\": []}";
	}else{
		result = "{\"matches\": [";
		std::map<int, Match*>::iterator iterMatches = matches.begin();

		for (; iterMatches != matches.end(); ++iterMatches){
			std::string user = users.get(iterMatches->first);
			result += user + ", ";
		}

		result[result.length()-2] = ']';
		result[result.length()-1] = '}';
	}

	//Sends response to the client containing its data
	Response response(ACCEPTED_STATUS, result);
	RequestHandler::sendResponse(response, request.getNetworkConnection());
}
