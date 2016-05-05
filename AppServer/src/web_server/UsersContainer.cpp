#include "UsersContainer.h"
#include <string>
#include <iostream>
#include <sstream>
#include "Response.h"

/**	Forms a json with specified values, and delegates the send
 *  in the web client. Adds a user to the system.
 *  TODO: some fields are hardcoded!
 */
void UsersContainer::add(
		Response& responseToClient,
		const std::string &userName,
		const std::string &userPassword,
		const std::string &userRealName,
		const std::string &userMail,
		const std::string &userBirthday,
		const std::string &userSex){
	std::stringstream ss;
	ss <<
			"{"
				"\"user\":"
				"{"
					"\"interests\":["
						"{\"category\":\"music\",\"value\":\"Pink Floyd\"}"
					"],"
					"\"name\": \"" 	<< userName 	<< "\","
					"\"alias\": \"" << userRealName << "\","
					"\"email\": \"" << userMail 	<< "\","
					"\"sex\": \"" 	<<  userSex 	<< "\","
					"\"location\":"
					"{"
						"\"latitude\": " << 213 << ","
						"\"longitud\": " << 6 <<
					"}"
				"}"
			"}";

	int id = client.sendRegister(ss.str());
	std::cout << "new client id: " << id << std::endl;
}

/** Forms a json with specified values, and delegates the send
 *  in the web client. Gets the information of a user in the system.
 *  TODO: some fields are hardcoded!
 */
void UsersContainer::get(const std::string &userName){
	client.sendLogin(std::string(""));
}
