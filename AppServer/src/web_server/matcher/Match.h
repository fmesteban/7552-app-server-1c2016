#ifndef WEB_SERVER_MATCHER_MATCH_H_
#define WEB_SERVER_MATCHER_MATCH_H_

#include "User.h"
#include "Chat.h"

class Match {
private:
	User &userA;
	User &userB;
	Chat chat;
public:
	Match(User &userA, User &userB);
	User &getUserA();
	User &getUserB();
	void pushChatMessage(User &userSrc, const std::string &message, const std::string &time);
	~Match();
};

#endif
