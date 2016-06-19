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

void Match::pushChatMessage(User &userSrc, const std::string &message){
	chat.pushMessage(userSrc, message);
}

Match::~Match() {
}

