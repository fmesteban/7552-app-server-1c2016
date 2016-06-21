#include "User.h"
#include "Interest.h"
#include <string>
#include <sstream>
#include <vector>
#include <cstdio>
#include <ctime>
#include <utility>
#include "Suggestion.h"
#include "Match.h"

/** User constructor
 *
 */
User::User(const std::string &name,
		const std::string &alias,
		const std::string &password,
		const std::string &email,
		int age,
		const std::string &sex, float longitude, float latitude,
		const std::string &photoProfile) :
		name(name),
		alias(alias),
		password(password),
		sex(sex),
		age(age),
		email(email),
		longitude(longitude),
		latitude(latitude),
		photoProfile(photoProfile){
	id = -1;
}

/** TODO: User should be able to be loaded from database.
 *
 */
User::User(Database &db, const std::string &email){
}

/* db registers: (email, id) */
void User::saveIn(Database &db){
	std::stringstream ss;
	ss << id;
	db.putKeyValue(email, ss.str());
	Log::instance()->append("User with email " + email + " saved in DB.",
			Log::INFO);
}

/** Adds an interest to user.
 *
 */
void User::addInterest(const std::string& category, const std::string &value){
	interests.push_back(new Interest(category, value));
}

/** Sets the user id, passed as int.
 *
 */
void User::setId(int id){
	this->id = id;
}

int User::getID(){
	return id;
}

float User::getLongitude(){
	return longitude;
}

float User::getLatitude(){
	return latitude;
}

std::vector<Interest*> User::getInterests(){
	return interests;
}

/** Sets the user id, passed as std::string.
 *
 */
void User::setId(const std::string& id){
	std::stringstream ss;
	ss << id;
	int idAsInt;
	ss >> idAsInt;
	setId(idAsInt);
}

/** Overloads the operator<<. User must know how print itself.
 *
 */
std::ostream& operator<<(std::ostream &os, const User& self) {
	os << "{\"user\":{";
	self.printInterests(os);
	if(self.id != -1)
		os << "\"id\": " 	<< self.id			<< ",";

	os <<
			"\"name\": \"" 	<< self.name 		<< "\","
			"\"alias\": \"" << self.alias 	<< "\","
			"\"email\": \"" << self.email 		<< "\","
			"\"sex\": \"" 	<< self.sex 		<< "\","
			"\"photo_profile\": \"" << self.photoProfile << "\","
			"\"age\": " << self.age << ","
			"\"location\":"
			"{"
			"\"latitude\": " << self.latitude << ","
			"\"longitude\": " << self.longitude <<
			"}"
			"}"
			"}";

	return os;
}


/** Builds the interests json list
 *
 */
void User::printInterests(std::ostream &os) const{
	os << 
			"\"interests\":[";
	if (!interests.empty()){
		for (size_t i=0; i < interests.size() - 1; ++i){
			/* with comma */
			os << *interests[i] << ",";
		}
		/* without comma */
		os << *interests[interests.size() - 1];
	}
	os << "],";
}

/** Returns a reference to user's email.
 *
 */
const std::string &User::getEmail() const{
	return email;
}

void User::addSuggestion(Suggestion* newSuggestion){
	sugestions.insert(std::pair<int,Suggestion*>(
			newSuggestion->getAnotherID(*this),newSuggestion));
}

void User::edit(User& newProfile){
	this->age = newProfile.age;
	this->alias = newProfile.alias;
	this->latitude = newProfile.latitude;
	this->longitude = newProfile.longitude;
	this->name = newProfile.name;
	this->photoProfile = newProfile.photoProfile;
	this->sex = newProfile.sex;

	std::vector<Interest*>::iterator interestIter = interests.begin();
	for(; interestIter != interests.end(); ++interestIter)
		delete *interestIter;
	interests.clear();

	interestIter = newProfile.interests.begin();
	for(; interestIter != newProfile.interests.end(); ++interestIter)
		addInterest((*interestIter)->getCategory(), (*interestIter)->getValue());
}

std::string User::getSomeInterestFromCategory(std::string &category){
	std::vector<Interest*>::iterator interestIter = interests.begin();
	for(; interestIter != interests.end(); ++interestIter)
		if((*interestIter)->getCategory() == category)
			return (*interestIter)->getValue();
	return std::string("any");
}

/** Checks needed preconditions
 *
 */
bool User::couldMatch(User &another){
	std::string category("sex");
	std::string myPreference =  this->getSomeInterestFromCategory(category);
	std::string otherPreference =  another.getSomeInterestFromCategory(category);
	if(myPreference == another.getSex() || myPreference == "any"){
		if(otherPreference == getSex() || otherPreference == "any"){
			return true;
		}
		return false;
	}
	return false;
}

std::string User::getSex(){
	if (sex == "male" || sex == "Male"){
		return "men";
	}
	return "women";
}

void User::dislike(int idAnother){
	std::map<int, Suggestion*>::iterator iter = sugestions.find(idAnother);
	if (iter != sugestions.end())
		iter->second->markAsDisliked();
}

Suggestion *User::getSuggestion(int idAnother){
	std::map<int, Suggestion*>::iterator iter = sugestions.find(idAnother);
	if (iter != sugestions.end())
		return iter->second;
	else
		return NULL;
}

void User::addMatch(int idAnother, Match *newMatch){
	this->matches.insert(std::pair<int,Match*>(idAnother,newMatch));
}

bool User::operator==(User &another){
	return this->id == another.id;
}

std::map<int, Match*> &User::getMatches(){
	return matches;
}

void User::sendMsg(int idDest, const std::string &message, const std::string &time){
	std::map<int, Match*>::iterator iterMatches = matches.find(idDest);
	if(iterMatches != matches.end()){
		iterMatches->second->pushChatMessage(*this, message, time);
	}
}

void User::printChat(std::ostream &os, int idAnother){
	if (matches.size() == 0)
		os << "\"messages\": []";
	std::map<int, Match*>::iterator iterMatches = matches.find(idAnother);
	if(iterMatches != matches.end()){
		os << iterMatches->second->getChat();
	}
}

/** Releases user's allocated resources.
 *
 */
User::~User(){
	std::vector<Interest*>::iterator interest = interests.begin();
	for(; interest != interests.end(); ++interest)
		delete *interest;

	interests.clear();
}
