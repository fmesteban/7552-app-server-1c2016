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
	RequestHandler::sendHttpOk(
			request.getNetworkConnection(),
			"{ \"response\": \"OK \" }\r\n");
}
