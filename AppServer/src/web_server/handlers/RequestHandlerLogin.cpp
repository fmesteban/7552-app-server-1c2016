#include "RequestHandlerLogin.h"
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
	if (request.getMethod() != "POST"){
		RequestHandler::sendHttpOk(
				request.getNetworkConnection(),
				"{ \"response\": \"POST\" }\r\n");
		return;
	}
	Json::Value root;
	Json::Reader reader;
	bool parsingSuccessful = reader.parse(request.getBody(), root);
	if (!parsingSuccessful){
		/* Bad Request */
	}

	std::string email = root.get("email", "unavailable").asString();
	std::string password = root.get("password", "unavailable").asString();

	std::string userAsString = users.login(email, password);

	RequestHandler::sendHttpOk(
			request.getNetworkConnection(),
			userAsString + "\r\n");
}
