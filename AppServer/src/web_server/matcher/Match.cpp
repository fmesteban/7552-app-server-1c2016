/** Include area. */
#include "Match.h"

Match::Match(User &userA, User &userB) :
	userA(userA),
	userB(userB),
	chat(userA, userB) {
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

/** Overloads the operator << from std::ostream
 *
 */
std::ostream& operator<<(std::ostream &os, const Match& self) {
	return os <<
		"{"
			"\"userA\":\"" << self.userA.getID() << "\","
			"\"userB\":\"" << self.userB.getID() << "\","
			"\"chat\":" << self.chat <<
		"}";
}

Match::~Match() {
}
