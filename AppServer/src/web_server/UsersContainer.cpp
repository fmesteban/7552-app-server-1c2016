#include "UsersContainer.h"
#include <string>
#include <iostream>
#include <sstream>
#include <utility>


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

