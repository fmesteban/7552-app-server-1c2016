#ifndef WEB_SERVER_USERSCONTAINER_H_
#define WEB_SERVER_USERSCONTAINER_H_

#include "WebClient.h"
#include "User.h"
#include "Database.h"
#include <string>
#include <map>
#include <list>

class UsersContainer {
private:
	WebClient client;
	Database db;
	std::map<int, User*> usersById;
public:
	UsersContainer();
	int add(User &newUser);
	void edit(User &newProfile);
	std::string login(const std::string &email);
	std::string get(const int id);
	int getID(const std::string &email);
	User *getUser(int userID);
	void getRandomUsers(std::list<User*> &randomUsers);
	~UsersContainer();
};

#endif
