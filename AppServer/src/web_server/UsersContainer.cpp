#include "UsersContainer.h"
#include <string>
#include <iostream>
#include <sstream>


/**	Forms a json with specified values, and delegates the send
 *  in the web client.
 *  TODO: some fields are hardcoded!
 */
void UsersContainer::add(
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

	client.sendRegister(ss.str());
}

