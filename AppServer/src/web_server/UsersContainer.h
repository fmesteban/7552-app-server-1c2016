#ifndef WEB_SERVER_USERSCONTAINER_H_
#define WEB_SERVER_USERSCONTAINER_H_

#include <string>
#include "WebClient.h"

class UsersContainer {
private:
	WebClient client;
public:
	void add(
			const std::string &userName,
			const std::string &userPassword,
			const std::string &userRealName,
			const std::string &userMail,
			const std::string &userBirthday,
			const std::string &userSex);
};

#endif
