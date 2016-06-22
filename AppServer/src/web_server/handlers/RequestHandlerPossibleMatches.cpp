#include "RequestHandlerPossibleMatches.h"
#include "Response.h"
#include "User.h"
#include <iostream>
#include <string>

RequestHandlerPossibleMatches::RequestHandlerPossibleMatches(
		UsersContainer &users, SuggestionsGenerator &suggestionsGenerator) :
		users(users),
		suggestionsGenerator(suggestionsGenerator),
		RequestHandler("/getpossiblematches") {
}

/** Parse the /getpossiblematches uri input, and saves it in the app-server
 *  database.
 *
 */
void RequestHandlerPossibleMatches::run(Request &request){
	Log::instance()->append("Received a get possible matches request", Log::INFO);

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
	std::string count = root.get("count", "unavailable").asString();

	if(email == "unavailable" || count == "unavailable"){
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
	 * Devolver el array en forma de json al cliente. */

	int userID = users.getID(email);

	if (userID == -1){
		Response response(SERVER_ERROR_STATUS, SERVER_ERROR_MSG);
		RequestHandler::sendResponse(response, request.getNetworkConnection());
		Log::instance()->append(
			"User with email: " + email + "not found.",
			Log::ERROR);
		return;
	}

	int count_i;
	std::stringstream(count) >> count_i;

	std::list<int> suggestions = suggestionsGenerator.getPossibleMatches(userID, count_i);

	std::string result;
	if (suggestions.size() == 0){
		result = "{\"possibleMatches\": []}";
	}else{
		result = "{\"possibleMatches\": [";

		for (auto const &s : suggestions){
			std::string user = users.get(s);
			result += user + ", ";
		}

		result[result.length()-2] = ']';
		result[result.length()-1] = '}';
	}
	
	Response response(ACCEPTED_STATUS, result);
	RequestHandler::sendResponse(response, request.getNetworkConnection());
}
