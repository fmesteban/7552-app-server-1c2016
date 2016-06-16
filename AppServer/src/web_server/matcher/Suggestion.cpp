#include "Suggestion.h"

Suggestion::Suggestion(User &userA, User &userB) :
	userA(userA),
	userB(userB) {
	AlikesB = false;
	BlikesA = false;
	_someoneDisliked = false;
	userA.addSuggestion(this);
	userB.addSuggestion(this);
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

Suggestion::~Suggestion() {
}

