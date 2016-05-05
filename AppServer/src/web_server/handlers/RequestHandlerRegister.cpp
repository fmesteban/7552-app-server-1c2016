#include "RequestHandlerRegister.h"
#include <iostream>
#include <string>
#include "Response.h"


RequestHandlerRegister::RequestHandlerRegister(UsersContainer &users) :
users(users),
RequestHandler("/register") {
}


/** Parse the register uri input, and saves it in the app-server
 * 	database.
 *
 */
void RequestHandlerRegister::run(Request &request){
	Json::Value root;
	Json::Reader reader;
	bool parsingSuccessful = reader.parse(request.getBody(), root);
	if(!parsingSuccessful){
		/* malformed json data */
	}

	std::string userName =
			root.get("userName", "unavailable field").asString();
	std::string userPassword =
			root.get("userPassword", "unavailable field").asString();
	std::string userRealName =
			root.get("userRealName", "unavailable field").asString();
	std::string userMail =
			root.get("userMail", "unavailable field").asString();
	std::string userBirthday =
			root.get("userBirthday", "unavailable field").asString();
	std::string userSex =
			root.get("userSex", "unavailable field").asString();

	std::cout << "name: " << userName << std::endl;
	std::cout << "pass: " << userPassword << std::endl;
	std::cout << "real: " << userRealName << std::endl;
	std::cout << "mail: " << userMail << std::endl;
	std::cout << "birth: " << userBirthday << std::endl;
	std::cout << "sex: " << userSex << std::endl;

	/* TODO: decidir si deberia pasar por parametro la response al client, o la
	 * del shared (para delegar el completado), o si se deberia completar aca
	 * y no pasar ninguna.
	 */
	Response responseToClient;
	users.add(responseToClient,
				userName,
				userPassword,
				userRealName,
				userMail,
				userBirthday,
				userSex);

	RequestHandler::sendHttpOk(
				request.getNetworkConnection(),
				"{ \"response\": \"OK\" }\r\n");
}
