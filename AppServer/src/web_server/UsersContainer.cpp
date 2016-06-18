#include "UsersContainer.h"
#include <string>
#include <iostream>
#include <sstream>
#include <utility>
#include <map>
#include <list>
#include <cstdlib>


UsersContainer::UsersContainer(){
	client.getUsers(usersById);
/*
	std::cout << "Users loaded from shared: " << usersById.size() << "\n\n";

	std::map<int, User*>::iterator iterUsers = usersById.begin();
	for(; iterUsers != usersById.end(); ++iterUsers){
		std::cout << "User " << iterUsers->first << ": \n\n" << *(iterUsers->second) <<
				"\n\n" << std::endl;
	}
*/
}

/** Forms a json with specified values, and delegates the send
 *  in the web client. Adds a user to the system.
 *  Returns the error message from the shared server.
 */
int UsersContainer::add(User &newUser){
	std::stringstream ss;
	ss << newUser;

	std::pair<int, int> status_pair = client.sendRegister(ss.str());
	int id = status_pair.first;

	if (status_pair.first != -1){
		newUser.setId(id);
		newUser.saveIn(db);
		usersById.insert(std::pair<int,User*>(id, &newUser));
	}else{
		delete &newUser;
	}

	return status_pair.second;
}


/** Loads user from db, and sends an edit profile request to
 *  shared server.
 */
void UsersContainer::edit(User &newProfile){
	std::stringstream ss;

	std::string userID;
	if(!db.getValue(newProfile.getEmail(), userID))
		return;

	ss.clear();
	newProfile.setId(userID);
	ss << newProfile;

	usersById.find(newProfile.getID())->second->edit(newProfile);

	client.sendEditProfile(ss.str(), userID);
}


/** Loads user id from db, and gets its data from shared server.
 *
 */
std::string UsersContainer::login(const std::string &email){
	std::string userID;
	if(!db.getValue(email, userID))
		return "";
	return client.sendLogin(userID);
}

/*
 * Returns the ID of user from the email
 */
int UsersContainer::getID(const std::string &email){
	std::string userID;
	if(!db.getValue(email, userID))
		return -1;
	int ID;
	return std::stringstream(userID) >> ID ? ID : 0;
}

/*
 *
 */
std::string UsersContainer::get(const int id){
	return client.sendLogin(std::to_string(id));
}


User *UsersContainer::getUser(int userID){
	std::map<int, User*>::iterator elem = usersById.find(userID);
	if (elem == usersById.end())
		return NULL;
	else
		return elem->second;
}


#define USERS_CONTAINER_RANDOM_USERS_NUMBER 5

void UsersContainer::getRandomUsers(std::list<User*> &randomUsers){
	if (usersById.size() == 0)
		return;
	for (int i = 0; i < USERS_CONTAINER_RANDOM_USERS_NUMBER; ++i){
		std::map<int, User*>::iterator iterUsers = usersById.begin();
		int r = std::rand() % usersById.size();
		for (int j = 0; j < r; ++j)
			++iterUsers;
		randomUsers.push_back(iterUsers->second);
	}
}


UsersContainer::~UsersContainer(){
	std::map<int, User*>::iterator iterUsers = usersById.begin();
	for(; iterUsers != usersById.end(); ++iterUsers)
		delete iterUsers->second;
	usersById.clear();
}

