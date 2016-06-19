#include "RequestHandlerSendConversation.h"
#include "Response.h"
#include "User.h"
#include <iostream>
#include <string>
#include <ctime>

RequestHandlerSendConversation::RequestHandlerSendConversation(UsersContainer &users) :
users(users),
RequestHandler("/sendconversation") {
}

/** Parse the /sendconversation uri input, and saves it in the app-server
 *  database.
 *
 */
void RequestHandlerSendConversation::run(Request &request){
	Log::instance()->append("Received a get send conversation request", Log::INFO);

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

	std::string emailSrc = root["conversation"]["emailSrc"].asString();
	std::string emailDst = root["conversation"]["emailDst"].asString();
	User *userSrc = users.getUser(users.getID(emailSrc));
	int idDest = users.getID(emailDst);

	std::time_t now = std::time(NULL);
	std::stringstream ssNow;
	//ssNow << now.tm_hour << ":" << now.tm_min;
	ssNow << "13:30";

	Json::Value &messages = root["conversation"]["messages"];
	Json::ValueConstIterator it = messages.begin();
	for (; it != messages.end(); ++it)
	{
		const Json::Value& msg = *it;
		std::string message = msg["msg"].asString();
		userSrc->sendMsg(idDest, message, ssNow.str());
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
