#include "RequestHandlerLogin.h"
#include "Response.h"
#include <iostream>
#include <string>

RequestHandlerLogin::RequestHandlerLogin(UsersContainer &users) :
users(users),
RequestHandler("/login") {
}

/** Should send the data of the user to the shared server. This should return
 *  all the fields of the user.
 *
 */
void RequestHandlerLogin::run(Request &request){
	Log::instance()->append("Received a login request", Log::INFO);
	if (request.getMethod() != "POST"){
		RequestHandler::sendHttpOk(
				request.getNetworkConnection(),
				"{ \"response\": \"POST\" }\r\n");
		Log::instance()->append("Not a POST request. Rejected.", Log::INFO);
		return;
	}
	Json::Value root;
	Json::Reader reader;
	bool parsingSuccessful = reader.parse(request.getBody(), root);
	if (!parsingSuccessful){
		Response response(BAD_REQUEST_STATUS, BAD_REQUEST_MSG);
		RequestHandler::sendResponse(response, request.getNetworkConnection());
		Log::instance()->append("Received a BAD (malformed) REQUEST. Rejected.", Log::INFO);
		return;
	}

	std::string email = root.get("email", "unavailable").asString();
	std::string password = root.get("password", "unavailable").asString();

	if(email == "unavailable" || password == "unavailable"){
		Response response(BAD_REQUEST_STATUS, BAD_REQUEST_MSG);
		RequestHandler::sendResponse(response, request.getNetworkConnection());
		Log::instance()->append("Received a BAD (incomplete) REQUEST. Rejected.", Log::INFO);
		return;		
	}

	std::cout << "email: " << email << std::endl;
	std::cout << "password: " << password << std::endl;
	
	std::string userAsString = users.login(email, password);

	Response response(ACCEPTED_STATUS, ACCEPTED_MSG);
	RequestHandler::sendResponse(response, request.getNetworkConnection());
	Log::instance()->append("Received an OK REQUEST. Accepted.", Log::INFO);
}
