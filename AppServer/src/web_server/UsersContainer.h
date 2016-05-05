#ifndef WEB_SERVER_USERSCONTAINER_H_
#define WEB_SERVER_USERSCONTAINER_H_

#include <string>
#include "WebClient.h"
#include "Response.h"

class UsersContainer {
private:
	WebClient client;
public:
	void add(Response& response,
			const std::string &userName,
			const std::string &userPassword,
			const std::string &userRealName,
			const std::string &userMail,
			const std::string &userBirthday,
			const std::string &userSex);
	// TODO: need ID to get user
    void get(
            const std::string &userName);
};

#endif
