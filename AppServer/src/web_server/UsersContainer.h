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
	int add(User &newUser);
	void edit(User &newProfile);
	std::string login(const std::string &email, const std::string &password);
};

#endif
