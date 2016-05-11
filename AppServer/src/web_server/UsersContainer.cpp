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
	return id != -1;
}

/** Forms a json with specified values, and delegates the send
 *  in the web client. Gets the information of a user in the system.
 *  TODO: some fields are hardcoded!
 */
void UsersContainer::get(const std::string &userName){
	client.sendLogin(std::string(""));
}
