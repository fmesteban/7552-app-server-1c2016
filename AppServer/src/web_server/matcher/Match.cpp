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

void Match::pushChatMessage(User &userSrc, const std::string &message, const std::string &time){
	chat.pushMessage(userSrc, message, time);
}

Chat &Match::getChat(){
	return chat;
}

Match::~Match() {
}

