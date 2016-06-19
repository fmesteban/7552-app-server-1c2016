#include "Suggestion.h"

Suggestion::Suggestion(User &userA, User &userB) :
	userA(userA),
	userB(userB) {
	AlikesB = false;
	BlikesA = false;
	_someoneDisliked = false;
}

User &Suggestion::getUserA(){
	return userA;
}

User &Suggestion::getUserB(){
	return userB;
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
	if(userA.getID() == idSrc){
		std::cout << "Adding like from " << idSrc << " to " << idDest << std::endl;
		AlikesB = true;
	}
	else{
		std::cout << "Adding like from " << idDest << " to " << idSrc << std::endl;
		BlikesA = true;
	}
}

/** Overloads the operator << from std::ostream
 *
 */
std::ostream& operator<<(std::ostream &os, const Suggestion& self) {
	return os << 
		"{"
			"\"userA\":\"" << self.userA().getID() << "\","
			"\"userB\":\"" << self.userB().getID() << "\","
			"\"AlikesB\":\"" << self.AlikesB << "\","
			"\"BlikesA\":\"" << self.BlikesA << "\","
			"\"_someoneDisliked\":\"" << self._someoneDisliked << "\""
		"}";
}

Suggestion::~Suggestion() {
}

