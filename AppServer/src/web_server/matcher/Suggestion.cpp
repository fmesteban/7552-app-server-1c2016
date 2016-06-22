#include "Suggestion.h"

Suggestion::Suggestion(User &userA, User &userB) :
	userA(userA),
	userB(userB) {
	AlikesB = false;
	BlikesA = false;
	_someoneDisliked = false;
	sentToA = false;
	sentToB = false;
}

User &Suggestion::getUserA(){
	return userA;
}

User &Suggestion::getUserB(){
	return userB;
}

void Suggestion::setAlikesB(bool value){
	AlikesB = value;
}

void Suggestion::setBlikesA(bool value){
	BlikesA = value;
}

void Suggestion::setsomeoneDisliked(bool value){
	_someoneDisliked = value;
}

bool Suggestion::isMatch(){
	return (AlikesB && BlikesA && !_someoneDisliked);
}

int Suggestion::getAnotherID(User &requesterUser){
	if (userA.getID() == requesterUser.getID())
		return userB.getID();
	else
		return userA.getID();
}

bool Suggestion::someoneDisliked(){
	return _someoneDisliked;
}

Match *Suggestion::generateMatch(){
	if(isMatch())
		return new Match(userA, userB);
	else
		return NULL;
}

void Suggestion::markAsDisliked(){
	_someoneDisliked = true;
}

void Suggestion::addLike(int idSrc, int idDest){
	if(userA.getID() == idSrc)
		AlikesB = true;
	else
		BlikesA = true;
}

/** Overloads the operator << from std::ostream
 *
 */
std::ostream& operator<<(std::ostream &os, const Suggestion& self) {
	return os << 
		"{"
			"\"userA\":\"" << self.userA.getID() << "\","
			"\"userB\":\"" << self.userB.getID() << "\","
			"\"AlikesB\":\"" << self.AlikesB << "\","
			"\"BlikesA\":\"" << self.BlikesA << "\","
			"\"_someoneDisliked\":\"" << self._someoneDisliked << "\","
			"\"sentToA\":\"" << self.sentToA << "\","
			"\"sentToB\":\"" << self.sentToB << "\""
		"}";
}

void Suggestion::setSentToA(bool value){
	sentToA = value;
}

void Suggestion::setSentToB(bool value){
	sentToB = value;
}

bool Suggestion::wasSentToUser(User &user){
	return (user == userA) ? sentToA : sentToB;
}

void Suggestion::setWasSentToUser(User &user, bool value){
	if (user == userA)
		setSentToA(value);
	else
		setSentToB(value);
}

Suggestion::~Suggestion() {
}

