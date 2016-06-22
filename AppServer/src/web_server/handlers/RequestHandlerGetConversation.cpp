#include "RequestHandlerGetConversation.h"
#include "Response.h"
#include "User.h"
#include <iostream>
#include <string>

RequestHandlerGetConversation::RequestHandlerGetConversation(UsersContainer &users) :
users(users),
RequestHandler("/getconversation") {
}

/** Parse the /getconversation uri input, and saves it in the app-server
 *  database.
 *
 */
void RequestHandlerGetConversation::run(Request &request){
	Log::instance()->append("Received a get conversation request", Log::INFO);

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

	if(emailSrc == "unavailable" || emailDst == "unavailable"){
		Response response(BAD_REQUEST_STATUS, BAD_REQUEST_MSG);
		RequestHandler::sendResponse(response, request.getNetworkConnection());
		Log::instance()->append(
			"Received a BAD (incomplete) REQUEST. Rejected.",
			Log::INFO);
		return;
	}

	User *userSrc = users.getUser(users.getID(emailSrc));
	int idDest = users.getID(emailDst);

	std::stringstream responseStream;
	responseStream << "{ \"conversation\": { \"email\" : " << emailDst << ", ";
	userSrc->printChat(responseStream, idDest);
	responseStream << "} }";

	//Sends response to the client containing its data
	Response response(ACCEPTED_STATUS, responseStream.str());
	RequestHandler::sendResponse(response, request.getNetworkConnection());
}
