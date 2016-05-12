#ifndef WEB_SERVER_USERSCONTAINER_H_
#define WEB_SERVER_USERSCONTAINER_H_

#include "WebClient.h"
#include "User.h"
#include "Database.h"
#include <string>

class UsersContainer {
private:
	WebClient client;
	Database db;
public:
	bool add(User &newUser);
	std::string login(const std::string &email, const std::string &password);
	// TODO: need ID to get user
    void get(const std::string &userName);
};

#endif
