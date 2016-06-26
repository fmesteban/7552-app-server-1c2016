/** Include area. */
#include "User.h"
#include "Interest.h"
#include <string>
#include <sstream>
#include <vector>
#include <cstdio>
#include <ctime>
#include <utility>
#include <map>
#include <list>
#include "Suggestion.h"
#include "Match.h"


/*------------------------------------------------------------------------
 * 	Member Functions Implementations
 * ---------------------------------------------------------------------*/

/** User constructor
 *
 *	\param name
 *	\param alias
 *	\param password
 *	\param email
 *	\param age
 *	\param sex
 *	\param longitude
 *	\param latitude
 *	\param photoProfile Is the user's photo encoded in Base64.
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


/** Saves an user in a kv db. Registers format: (email, id).
 *
 *  \param db Is a refference to db where the user will be saved.
 */
void User::saveIn(Database &db){
	std::stringstream ss;
	ss << id;
	db.putKeyValue(email, ss.str());
	Log::instance()->append("User with email " + email + " saved in DB.",
			Log::INFO);
}

/** Adds an interest to user.
 *
 * 	\param category Is the category of the interest.
 * 	\param value Is a value possible for category.
 */
void User::addInterest(const std::string& category, const std::string &value){
	interests.push_back(new Interest(category, value));
}

/** Sets the user id, passed as int.
 *
 *	\param id The identifier as int.
 */
void User::setId(int id){
	this->id = id;
}


/** Gets the user id, as int.
 *
 *	\return The identifier as int.
 */
int User::getID(){
	return id;
}


/** Gets the users longitude.
 *
 *	\return The longitude.
 */
float User::getLongitude(){
	return longitude;
}


/** Gets the users latitude.
 *
 *	\return The latitude.
 */
float User::getLatitude(){
	return latitude;
}


/** Gets the user's interests.
 *
 *	\return a refference to user's array of interests.
 */
std::vector<Interest*> &User::getInterests(){
	return interests;
}


/** Sets the user id, passed as std::string.
 *
 *	\param id The user identifier, passed as string.
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
 *	\param os Is the output stream.
 *	\param self Is the current instance of User.
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


/** Builds the interests json list.
 *
 *	\param os Is the output stream.
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
 *	\return a reference to user's email.
 */
const std::string &User::getEmail() const{
	return email;
}


/** Adds a suggestion to user's suggestions map.
 *
 * 	\param newSuggestion Is a pointer to the new Suggestion to be added.
 */
void User::addSuggestion(Suggestion* newSuggestion){
	sugestions.insert(std::pair<int,Suggestion*>(
			newSuggestion->getAnotherID(*this),newSuggestion));
}


/** Updates User's data with \newProfile data.
 *
 * 	\param newProfile Is a refference to another profile what has the new data.
 */
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


/** Gets the first found interest for the passed \category.
 *
 * 	\param category Is the category to want in the interests array.
 *
 * 	\return the first found interest for the passed \category.
 */
std::string User::getSomeInterestFromCategory(std::string &category){
	std::vector<Interest*>::iterator interestIter = interests.begin();
	for(; interestIter != interests.end(); ++interestIter)
		if((*interestIter)->getCategory() == category)
			return (*interestIter)->getValue();
	return std::string("any");
}


/** Checks needed preconditions.
 *
 *	\param another Is another user to check if can match with this.
 *
 *	\return True if They aren't the same user, if they aren't already
 *	suggested to each other, and if they have compatible sexual orientations.
 */
bool User::couldMatch(User &another){
	/* check sexual orientations */
	bool sexualOrientationCouldMatch;
	std::string category("sex");
	std::string myPreference =  this->getSomeInterestFromCategory(category);
	std::string otherPreference =  another.getSomeInterestFromCategory(category);
	if(myPreference == another.getSex() || myPreference == "any"){
		if(otherPreference == getSex() || otherPreference == "any"){
			sexualOrientationCouldMatch = true;
		}else{
			sexualOrientationCouldMatch = false;
		}
	}else{
		sexualOrientationCouldMatch = false;
	}

	/* don't suggest myself */
	bool sameUser = (another == *this);

	/* already suggested */
	bool alreadySuggested = isAlreadySuggested(another.getID());

	return sexualOrientationCouldMatch && (!sameUser) && (!alreadySuggested);
}


/** Returns the user sex as string.
 *
 *	\return string representing the user sex.
 */
std::string User::getSex(){
	if (sex == "male" || sex == "Male"){
		return "men";
	}
	return "women";
}


/**	This instance puts a dislike to the user with id \idAnother.
 *
 * 	\param idAnother The identifier from the other user.
 */
void User::dislike(int idAnother){
	std::map<int, Suggestion*>::iterator iter = sugestions.find(idAnother);
	if (iter != sugestions.end())
		iter->second->markAsDisliked();
}


/** Gets the suggestion between this instance and the user with id \idAnother.
 *
 * 	\param idAnother The identifier from the other user.
 *
 * 	\return If found, a pointer to the suggestion, NULL ptr otherwise.
 */
Suggestion *User::getSuggestion(int idAnother){
	std::map<int, Suggestion*>::iterator iter = sugestions.find(idAnother);
	if (iter != sugestions.end())
		return iter->second;
	else
		return NULL;
}


/** Asks user if has the user with id \idAnother in its suggestions.
 *
 * 	\param idAnother The identifier from the other user.
 *
 * 	\return True if this instance has \idAnother in its suggestions array,
 * 	False otherwise.
 */
bool User::isAlreadySuggested(int idAnother){
	return (getSuggestion(idAnother) != NULL);
}


/** Adds a match to its corresponding array.
 *
 * 	\param idAnother The identifier from the other user.
 * 	\param newMatch Is a pointer to the new match instance.
 */
void User::addMatch(int idAnother, Match *newMatch){
	this->matches.insert(std::pair<int,Match*>(idAnother,newMatch));
}


/** Compares this instance with another.
 *
 * 	\param another Is a refference to the another instance of users.
 */
bool User::operator==(User &another){
	/* decide by identifier */
	return this->id == another.id;
}


/** Gets the internal matches map.
 *
 * 	\return A refference to the internal matches map.
 */
std::map<int, Match*> &User::getMatches(){
	return matches;
}


/** Appends a message to conversation with another user.
 *
 *	\param idDest Is the identifier of the other user (the destination).
 *	\param message Is the message as string.
 *	\param time Is a timestamp as string.
 */
void User::sendMsg(int idDest, const std::string &message,
		const std::string &time){
	std::map<int, Match*>::iterator iterMatches = matches.find(idDest);
	if(iterMatches != matches.end()){
		iterMatches->second->pushChatMessage(*this, message, time);
	}
}


/** Prints the messages sent from another user to this instance.
 *
 *  \param os Is the output stream.
 * 	\param idAnother The identifier from the other user.
 */
void User::printChat(std::ostream &os, int idAnother){
	os << "\"messages\": ";

	std::map<int, Match*>::iterator iterMatches = matches.find(idAnother);
	if(iterMatches != matches.end()){
		Match *match = iterMatches->second;
		User &anotherUser = match->getUserA() ==
				*this ? match->getUserB() : match->getUserA();
		match->getChat().printTo(os, anotherUser);
	}else{
		os << "[]";
	}
}


/** Adds the Suggestions seen by the other user (but not by this instance)
 * 	in a list of ids.
 *
 * 	\param result Is the list of identifiers.
 */
void User::loadNotShownSuggestions(std::list<int> &result){
	std::map<int, Suggestion*>::iterator iterSug = sugestions.begin();
	for (; iterSug != sugestions.end(); ++iterSug){
		if (!iterSug->second->wasSentToUser(*this)){
			result.push_back(iterSug->first);
			iterSug->second->setWasSentToUser(*this, true);
		}
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
