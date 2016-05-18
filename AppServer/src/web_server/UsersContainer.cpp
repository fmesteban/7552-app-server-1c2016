#include "UsersContainer.h"
#include <string>
#include <iostream>
#include <sstream>


/**	Forms a json with specified values, and delegates the send
 *  in the web client. Adds a user to the system.
 *  TODO: some fields are hardcoded!
 */
bool UsersContainer::add(User &newUser){
	std::stringstream ss;
	ss << newUser;

	std::cout << ss.str();

	int id = client.sendRegister(ss.str());
	std::cout << "new client id: " << id << std::endl;

	if (id != -1){
		newUser.setId(id);
		newUser.saveIn(db);
	}

	return id != -1;
}

void UsersContainer::edit(User &newProfile){
	std::stringstream ss;

	std::string userID;
	if(!db.getValue(newProfile.getEmail(), userID)){
		std::cerr << "email not found" << std::endl;
		return;
	}

	ss.clear();
	newProfile.setId(userID);
	ss << newProfile;

	std::cout << ss.str();

	client.sendEditProfile(ss.str(), userID);
}

std::string UsersContainer::login(
		const std::string &email,
		const std::string &password){
	std::string userID;
	db.getValue(email, userID);

	return client.sendLogin(userID);
}

