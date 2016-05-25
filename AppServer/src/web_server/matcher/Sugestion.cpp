#include "Sugestion.h"

Sugestion::Sugestion(User &userA, User &userB) :
	userA(userA),
	userB(userB) {
	AlikesB = false;
	BlikesA = false;
	_someoneDisliked = false;
}

bool Sugestion::isMatch(){
	return (AlikesB && BlikesA && !_someoneDisliked);
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

