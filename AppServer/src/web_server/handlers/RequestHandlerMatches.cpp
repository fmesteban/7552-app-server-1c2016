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

	if (request.getMethod() != "GET"){
		/* some libraries send OPTIONS before POST */
		RequestHandler::sendHttpOk(
			request.getNetworkConnection(),
			"{ \"response\": \"GET\" }\r\n");
		Log::instance()->append("Not a GET request. Rejected.", Log::INFO);
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

	/*
	Obtener el usuario de la DB
	Del SuggestionsGenerator (?) conseguir los matches.
	Hacer un get de cada user en el shared server
	Devolver el JSON

	int user_id = db.get(email);
	std::list<int> matches = suggestionGenerator.getMatches(user_id); // Should return IDs or emails?
	std::string result;
	for each match in Matches do
		std::string userAsString = users.login(match); //TODO change login for get
		
		if (userAsString == ""){
			Log::instance()->append(
					"User with email " + email + " was not found.", Log::ERROR);
		}
		append userAsString to new list
	end

	//Sends response to the client containing its data
	Response response(ACCEPTED, result);
	RequestHandler::sendResponse(response, request.getNetworkConnection());
	*/

}