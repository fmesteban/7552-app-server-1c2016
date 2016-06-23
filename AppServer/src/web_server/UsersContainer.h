#ifndef WEB_SERVER_USERSCONTAINER_H_
#define WEB_SERVER_USERSCONTAINER_H_

/** Include area. */
#include "WebClient.h"
#include "User.h"
#include "Database.h"
#include <json/json.h>
#include <string>
#include <map>
#include <list>
#include <vector>

class UsersContainer {
private:
	WebClient client;
	Database db;
	std::map<int, User*> usersById;
	std::vector<Match*> allMatches;
	bool loadMatches();
public:
	UsersContainer();
	Database &getDB();
	int add(User &newUser);
	int edit(User &newProfile);
	std::string login(const std::string &email);
	std::string get(const int id);
	int getID(const std::string &email);
	User *getUser(int userID);
	void getRandomUsers(std::list<User*> &randomUsers);
	void addMatch(Match *match);
	~UsersContainer();
};

#endif
