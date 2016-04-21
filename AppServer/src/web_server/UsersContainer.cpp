#include "UsersContainer.h"
#include <string>


void UsersContainer::add(
		const std::string &userName,
		const std::string &userPassword,
		const std::string &userRealName,
		const std::string &userMail,
		const std::string &userBirthday,
		const std::string &userSex){
	client.sendRegister(std::string(
		"{"
			"\"user\": {"
				"\"name\": \"usuario\","
				"\"alias\": \"not a user\","
				"\"email\": \"usuario@usuario.com\","
				"\"interests\": [{"
						"\"category\": \"music/band\","
						"\"value\": \"radiohead\" "
					"}, {"
						"\"category\": \"music/band\", "
						"\"value\": \"pearl jam\" "
					"},{"
						"\"category\": \"outdoors\", "
						"\"value\": \"running\" "
					"}"
				"],"
				"\"latitude\": ­121.45356,"
				"\"location\": {"
				"\"longitude\": 46.51119"
			"}"
		"}"
	));
}

