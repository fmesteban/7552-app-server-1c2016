#include "UsersContainer.h"
#include <string>
#include <iostream>
#include <sstream>
#include <utility>
#include <map>
#include <list>
#include <cstdlib>
#include "Match.h"

UsersContainer::UsersContainer(){
	client.getUsers(usersById);

	/* Add users to db. This way we can change of shared server without problems */
	std::map<int, User*>::iterator iterLoadedUsers = usersById.begin();
	for(; iterLoadedUsers != usersById.end(); ++iterLoadedUsers)
		iterLoadedUsers->second->saveIn(db);

	Log::instance()->append(
			"Loaded " + std::to_string(usersById.size()) + " users correctly from shared server.",
			Log::INFO);

	bool matchesLoaded = loadMatches();
	if(!matchesLoaded){
		Log::instance()->append(
				"There was an error loading matches from RocksDB.",
				Log::INFO);
	}
	else {
		Log::instance()->append(
				"Loaded " + std::to_string(allMatches.size()) + " matches correctly from RocksDB.",
				Log::INFO);
	}
}

/**
 * Returns the reference to the Database
 */
Database &UsersContainer::getDB(){
	return db;
}

/**
 * Loads matches saved in DB
 */
bool UsersContainer::loadMatches(){
	std::string matches_str;
	db.getValue(std::string("matches"), matches_str);

	std::cerr << "Matches loaded from DB\n" << matches_str << std::endl;

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
		if (userA == NULL || userB == NULL){
			std::cout << "null";
			continue;
		}else{
			std::cout << "loading " << userA->getID() << " & " << userB->getID() << std::endl;
		}

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
int UsersContainer::edit(User &newProfile){
	std::stringstream ss;

	std::string userID;
	if(!db.getValue(newProfile.getEmail(), userID))
		return -1;

	ss.clear();
	newProfile.setId(userID);
	ss << newProfile;

	usersById.find(newProfile.getID())->second->edit(newProfile);

	return client.sendEditProfile(ss.str(), userID);
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

/**
 * Returns a User* that matches the ID
 */
User *UsersContainer::getUser(int userID){
	std::map<int, User*>::iterator elem = usersById.find(userID);
	if (elem == usersById.end())
		return NULL;
	else
		return elem->second;
}


#define USERS_CONTAINER_RANDOM_USERS_NUMBER 15

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

void UsersContainer::addMatch(Match *match){
	allMatches.push_back(match);
	User &userA = match->getUserA();
	User &userB = match->getUserB();
	userA.addMatch(userB.getID(), match);
	userB.addMatch(userA.getID(), match);
}

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
	std::cout << "Matches to be saved on DB" << std::endl;
	std::cout << value.str() << std::endl;
	db.putKeyValue(key, value.str());
	allMatches.clear();

	std::map<int, User*>::iterator iterUsers = usersById.begin();
	for(; iterUsers != usersById.end(); ++iterUsers)
		delete iterUsers->second;
	usersById.clear();
}

