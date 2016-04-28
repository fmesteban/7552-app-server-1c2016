#include "RequestHandlerRegister.h"
#include <iostream>
#include <string>

RequestHandlerRegister::RequestHandlerRegister(UsersContainer &users) :
users(users),
RequestHandler("/register") {
}

/** Parse the register uri input, and saves it in the app-server
 * 	database. TODO: send the data to the shared-server
 *
 */
void RequestHandlerRegister::run(
		struct mg_connection *networkConnection,
		mg_str *body){
	std::cout << "body: " << body->p << std::endl;

	INIT_JSON;
	STRING_FROM_FIELD(userName);
	STRING_FROM_FIELD(userPassword);
	STRING_FROM_FIELD(userRealName);
	STRING_FROM_FIELD(userMail);
	STRING_FROM_FIELD(userBirthday);
	STRING_FROM_FIELD(userSex);

	std::cout << "name: " << userName << std::endl;
	std::cout << "pass: " << userPassword << std::endl;
	std::cout << "real: " << userRealName << std::endl;
	std::cout << "mail: " << userMail << std::endl;
	std::cout << "birth: " << userBirthday << std::endl;
	std::cout << "sex: " << userSex << std::endl;

	users.add(
			userName,
			userPassword,
			userRealName,
			userMail,
			userBirthday,
			userSex);

	RequestHandler::sendHttpOk(
			networkConnection,
			"{ \"response\": \"hello " + userName + "\" }\r\n");
}
