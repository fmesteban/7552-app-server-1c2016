#include "RequestHandlerMatches.h"
#include "Response.h"
#include "User.h"
#include <iostream>
#include <string>

RequestHandlerMatches::RequestHandlerMatches(UsersContainer &users) :
users(users),
RequestHandler("/getmatches") {
}

/** Parse the /getmatches uri input, and saves it in the app-server
 *  database.
 *
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
			"Received a BAD (malformed) REQUEST. Rejected.",
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

	std::map<int, Match*> &matches = users.getUser(users.getID(email))->getMatches();

	std::string result;
	if (matches.size() == 0){
		result = "{\"matches\": []}";
		Log::instance()->append(
			"Received a BAD (incomplete) REQUEST. Rejected.",
			Log::INFO);
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
