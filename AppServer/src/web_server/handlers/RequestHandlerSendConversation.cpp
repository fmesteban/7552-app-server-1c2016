/** Include area. */
#include "RequestHandlerSendConversation.h"
#include "Response.h"
#include "User.h"
#include <iostream>
#include <string>
#include <ctime>

/*------------------------------------------------------------------------
 * 	Member Functions Implementations
 * ---------------------------------------------------------------------*/

/** Request handler send conversation handles the uri "/sendconversation".
 *
 * 	\param users Is the server users container.
 */
RequestHandlerSendConversation::RequestHandlerSendConversation(
		UsersContainer &users) :
users(users),
RequestHandler("/sendconversation") {
}

/** Parse the /sendconversation uri input, and saves it in the app-server
 *  database.
 *
 *	\param request Is the request sent by client.
 */
void RequestHandlerSendConversation::run(Request &request){
	Log::instance()->append("Received a get send conversation request", Log::INFO);

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

	std::string emailSrc = root["conversation"]["emailSrc"].asString();
	std::string emailDst = root["conversation"]["emailDst"].asString();

	if(emailSrc == "unavailable" || emailDst == "unavailable"){
		Response response(BAD_REQUEST_STATUS, BAD_REQUEST_MSG);
		RequestHandler::sendResponse(response, request.getNetworkConnection());
		Log::instance()->append(
			"Received a BAD (incomplete) REQUEST. Some fields were missing. Rejected.",
			Log::INFO);
		return;
	}

	int idSrc = users.getID(emailSrc);
	int idDest = users.getID(emailDst);
	if (idSrc == -1 || idDest == -1){
		if(idSrc == -1){
			Log::instance()->append(
				"User with email: " + emailSrc + "was not found. Rejected.",
				Log::INFO);
		}else {
			Log::instance()->append(
				"User with email: " + emailDst + "was not found. Rejected.",
				Log::INFO);	
		}
		Response response(BAD_REQUEST_STATUS, BAD_REQUEST_MSG);
		RequestHandler::sendResponse(response, request.getNetworkConnection());
		return;
	}

	User *userSrc = users.getUser(idSrc);

	std::time_t _now = time(NULL);
	struct tm *now = localtime(&_now);
	std::stringstream ssNow;
	ssNow << now->tm_hour << ":" << now->tm_min;

	Json::Value &messages = root["conversation"]["messages"];
	Json::ValueConstIterator it = messages.begin();
	for (; it != messages.end(); ++it)
	{
		const Json::Value& msg = *it;
		std::string message = msg["msg"].asString();
		userSrc->sendMsg(idDest, message, ssNow.str());

		Log::instance()->append(
			"User " + emailSrc + " sends to user " + emailDst +
			"the following:\n" + message,
			Log::INFO);
	}
	
	/* Sends response to the client containing its data */
	Response response(ACCEPTED_STATUS, "{}");
	RequestHandler::sendResponse(response, request.getNetworkConnection());

	/* Updates token time */
	userSrc->revalidateToken();
}
