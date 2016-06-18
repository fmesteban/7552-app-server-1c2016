#include "RequestHandlerLike.h"
#include "Response.h"
#include "User.h"
#include <iostream>
#include <string>

RequestHandlerLike::RequestHandlerLike(UsersContainer &users) :
users(users),
RequestHandler("/like") {
}

/** Parse the /like uri input, and saves the like from User A to B
 *  database.
 *
 */
void RequestHandlerLike::run(Request &request){

	Log::instance()->append("Received a like request", Log::INFO);

	if (request.getMethod() != "PUT"){
		/* some libraries send OPTIONS before POST */
		RequestHandler::sendHttpOk(
			request.getNetworkConnection(),
			"{ \"response\": \"PUT\" }\r\n");
		Log::instance()->append("Not a PUT request. Rejected.", Log::INFO);
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

	if(emailSrc == "unavailable" || emailDst == "unavailable" ){
		Response response(BAD_REQUEST_STATUS, BAD_REQUEST_MSG);
		RequestHandler::sendResponse(response, request.getNetworkConnection());
		Log::instance()->append(
			"Received a BAD (incomplete) REQUEST. Rejected.",
			Log::INFO);
		return;
	}
}