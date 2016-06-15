#include "Suggestion.h"

Sugestion::Sugestion(User &userA, User &userB) :
	userA(userA),
	userB(userB) {
	AlikesB = false;
	BlikesA = false;
	_someoneDisliked = false;
	userA.addSuggestion(this);
	userB.addSuggestion(this);
}

bool Sugestion::isMatch(){
	return (AlikesB && BlikesA && !_someoneDisliked);
}

int Sugestion::getAnotherID(User &requesterUser){
	if (userA.getID() == requesterUser.getID())
		return userB.getID();
	else
		return userA.getID();
}

bool Sugestion::someoneDisliked(){
	return _someoneDisliked;
}

Match *Sugestion::generateMatch(){
	if(isMatch())
		return new Match(userA, userB);
	else
		return NULL;
}

Sugestion::~Sugestion() {
}

