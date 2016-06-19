#include "Match.h"

Match::Match(User &userA, User &userB) :
	userA(userA),
	userB(userB) {
}

User &Match::getUserA(){
	return userA;
}

User &Match::getUserB(){
	return userB;
}

Match::~Match() {
}

