/** Include area. */
#include "UsersContainer.h"
#include <string>
#include <iostream>
#include <sstream>
#include <utility>
#include <map>
#include <list>
#include <cstdlib>
#include "Match.h"


/** Constants. */
#define USERS_CONTAINER_RANDOM_USERS_NUMBER 15


/*------------------------------------------------------------------------
 * 	Member Functions Implementations
 * ---------------------------------------------------------------------*/

/** Constructor of users container.
 *
 */
UsersContainer::UsersContainer(){
	/* loads the users from shared server */
	client.getUsers(usersById);

	/* Add users to db. This way we can change of shared server without problems */
	std::map<int, User*>::iterator iterLoadedUsers = usersById.begin();
	for(; iterLoadedUsers != usersById.end(); ++iterLoadedUsers)
		iterLoadedUsers->second->saveIn(db);

	Log::instance()->append(
			"Loaded " + std::to_string(usersById.size()) +
			" users correctly from shared server.",
			Log::INFO);

	bool matchesLoaded = loadMatches();
	if(!matchesLoaded){
		Log::instance()->append(
				"There was an error loading matches from RocksDB.",
				Log::INFO);
	}else {
		Log::instance()->append(
				"Loaded " + std::to_string(allMatches.size()) +
				" matches correctly from RocksDB.",
				Log::INFO);
	}
}

/** Returns the reference to the Database.
 *
 * 	\return A refference to the database.
 */
Database &UsersContainer::getDB(){
	return db;
}

/** Loads matches saved in DB.
 *
 *	\return True on success, False otherwise.
 */
bool UsersContainer::loadMatches(){
	std::string matches_str;
	db.getValue(std::string("matches"), matches_str);

	/* Loads the request into a JSON Value object */
	Json::Value root;
	Json::Reader reader;
	bool parsingSuccessful = reader.parse(matches_str, root);
	if (!parsingSuccessful){
		Log::instance()->append(
				"JSON saved for matches is not correct.",
				Log::ERROR);
		return false;
	}

	/* Parse interests array */
	Json::Value& matches = root["matches"];
	Json::ValueConstIterator it = matches.begin();
	for (; it != matches.end(); ++it)
	{
		const Json::Value& match = *it;
		std::string userA_str = match.get("userA", "unavailable").asString();
		int userAID;
		std::stringstream(userA_str) >> userAID ? userAID : 0;
		std::string userB_str = match.get("userB", "unavailable").asString();
		int userBID;
		std::stringstream(userB_str) >> userBID ? userBID : 0;
		if(userA_str == "unavailable" || userB_str == "unavailable")
			continue;

		User* userA = getUser(userAID);
		User* userB = getUser(userBID);

		Match* newMatch = new Match(*userA, *userB);

		addMatch(newMatch);

		/* Need to parse chat messages still */
		const Json::Value& messages = match["chat"];
		Json::ValueConstIterator it = messages.begin();
		for (; it != messages.end(); ++it)
		{
			const Json::Value& chatMessage = *it;
			std::string from = chatMessage.get("sendFrom", "unavailable").asString();
			std::string msg = chatMessage.get("msg", "unavailable").asString();
			std::string time = chatMessage.get("time", "unavailable").asString();
			if(from == "unavailable" || msg == "unavailable" || time == "unavailable")
				continue;

			User* user = getUser(getID(from));

			newMatch->pushChatMessage(*user, msg, time);
		}
	}
	return true;
}

/** Forms a json with specified values, and delegates the send
 *  in the web client. Adds a user to the system.
 *
 *  \param newUser Is the profile from the new user.
 *
 *  \return The error message from the shared server.
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
 *
 *  \param newProfile Contains the new data for user.
 *
 *  \return -1 if user was not found in DB, or web client's return
 *  otherwise.
 */
int UsersContainer::edit(User &newProfile){
	std::stringstream ss;

	std::string userID;
	std::string email = newProfile.getEmail();
	if(!db.getValue(email, userID))
		return -1;

	ss.clear();
	newProfile.setId(userID);
	ss << newProfile;

	usersById.find(newProfile.getID())->second->edit(newProfile);

	return client.sendEditProfile(ss.str(), userID);
}

/** Loads user id from db, and gets its data from shared server.
 *
 *	\param email is the email from the user who wants to login.
 *
 *	\return the same return of shared server.
 */
std::string UsersContainer::login(const std::string &email){
	std::string userID;
	if(!db.getValue(email, userID))
		return "";
	return client.sendLogin(userID);
}

/** Returns the ID of user from the email
 *
 *	\param email Is the email from an user.
 *
 *	\return The user's ID if email is in DB, -1 otherwise.
 */
int UsersContainer::getID(const std::string &email){
	std::string userID;
	if(!db.getValue(email, userID))
		return -1;
	int ID;
	return std::stringstream(userID) >> ID ? ID : 0;
}

/** Gets a user from shared server.
 * 
 * 	\param id Is the identifier of user to get.
 *
 * 	\return user json as string.
 */
std::string UsersContainer::get(const int id){
	return client.sendLogin(std::to_string(id));
}

/** Returns a User pointer that matches the ID.
 *
 * 	\param id Is the identifier of user to get.
 *
 *	\return The user with identifier \id if it is in container, or NULL
 *	otherwise.
 */
User *UsersContainer::getUser(int userID){
	std::map<int, User*>::iterator elem = usersById.find(userID);
	if (elem == usersById.end())
		return NULL;
	else
		return elem->second;
}

/** Fills a list of random user pointers.
 *
 * 	\param randomUsers Is the list to fill.
 */
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

/** Adds a match to the internal matches array, and to
 *  corresponding users.
 *
 *	\param match Is the new match.
 */
void UsersContainer::addMatch(Match *match){
	allMatches.push_back(match);
	User &userA = match->getUserA();
	User &userB = match->getUserB();
	userA.addMatch(userB.getID(), match);
	userB.addMatch(userA.getID(), match);
}

/** Persist current state and releases reserver resources.
 *
 */
UsersContainer::~UsersContainer(){
	std::string key("matches");
	std::ostringstream value;
	value << "{\"matches\":[";
	if (!allMatches.empty()){
		for (int i = 0; i < allMatches.size() - 1; ++i){
			value << *allMatches[i] << ",";
			delete allMatches[i];
		}
		value << *allMatches[allMatches.size() - 1];
		delete allMatches[allMatches.size() - 1];
	}
	value << "]}";
	Log::instance()->append(
			"Matches to be saved on DB:\n" + value.str(),
			Log::INFO);
	db.putKeyValue(key, value.str());
	allMatches.clear();

	std::map<int, User*>::iterator iterUsers = usersById.begin();
	for(; iterUsers != usersById.end(); ++iterUsers)
		delete iterUsers->second;
	usersById.clear();
}

