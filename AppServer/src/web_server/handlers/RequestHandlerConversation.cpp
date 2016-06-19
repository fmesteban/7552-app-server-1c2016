#include "RequestHandlerConversation.h"
#include "Response.h"
#include "User.h"
#include <iostream>
#include <string>

RequestHandlerConversation::RequestHandlerConversation(UsersContainer &users) :
users(users),
RequestHandler("/getconversation") {
}

/** Parse the /getconversation uri input, and saves it in the app-server
 *  database.
 *
 */
void RequestHandlerConversation::run(Request &request){
	Log::instance()->append("Received a get conversation request", Log::INFO);

	if (request.getMethod() != "POST"){
		/* some libraries send OPTIONS before POST */
		RequestHandler::sendHttpOk(
			request.getNetworkConnection(),
			"{ \"response\": \"POST\" }\r\n");
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

	/*
	Obtener el usuario de cada email
	Llamar a SuggestionsGenerator y conseguir la conversation entre ambos
	Devolver el JSON

	int user_id_src = db.get(emailSrc);
	int user_id_dst = db.get(emailDst);
	Conversation conversation = suggestionGenerator.getConversation(user_id_src, user_id_dst);
	std::string conversationAsString << conversation;
	
	//Sends response to the client containing its data
	Response response(ACCEPTED, conversationAsString);
	RequestHandler::sendResponse(response, request.getNetworkConnection()); */
}
