#include "RequestHandlerPossibleMatches.h"
#include "Response.h"
#include "User.h"
#include <iostream>
#include <string>

RequestHandlerPossibleMatches::RequestHandlerPossibleMatches(UsersContainer &users) :
users(users),
RequestHandler("/getpossiblematches") {
}

/** Parse the /getpossiblematches uri input, and saves it in the app-server
 *  database.
 *
 */
void RequestHandlerPossibleMatches::run(Request &request){
	Log::instance()->append("Received a get possible matches request", Log::INFO);

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
	std::string count = root.get("count", "unavailable").asString();

	if(email == "unavailable" || count = "unavailable"){
		Response response(BAD_REQUEST_STATUS, BAD_REQUEST_MSG);
		RequestHandler::sendResponse(response, request.getNetworkConnection());
		Log::instance()->append(
			"Received a BAD (incomplete) REQUEST. Rejected.",
			Log::INFO);
		return;
	}

	/* Obtener el ID del usuario de la DB.
	 * Llamar a getPossibleMatches del SuggestionsGenerator (tener referencia o hacer un singleton?)
	 * LLamar al shared haciendo get de cada user suggested. Y guardar la info en un array
	 * Devolver el array en forma de json al cliente.
	int user_id = db.get(email);
	std::list<int> possibleMatches = suggestionGenerator.getPossibleMatches(user_id, count); // Should return IDs or emails?
	std::string result;
	for each possibleMatch in possibleMatches do
		std::string userAsString = users.login(possibleMatch); //TODO change login for get
		
		if (userAsString == ""){
			Log::instance()->append(
					"User with email " + email + " was not found.", Log::ERROR);
		}
		append to new list
	end

	//Sends response to the client containing its data
	Response response(ACCEPTED, result);
	RequestHandler::sendResponse(response, request.getNetworkConnection()); */

}