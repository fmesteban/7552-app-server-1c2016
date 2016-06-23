#ifndef WEB_SERVER_MATCHER_MATCH_H_
#define WEB_SERVER_MATCHER_MATCH_H_

/** Include area. */
#include "User.h"
#include "Chat.h"
#include <string>

class Match {
private:
	User &userA;
	User &userB;
	Chat chat;
public:
	Match(User &userA, User &userB);
	User &getUserA();
	User &getUserB();
	void pushChatMessage(
		User &userSrc, 
		const std::string &message, 
		const std::string &time);
	friend std::ostream & operator<<(std::ostream &os, const Match& self);
	Chat &getChat();
	~Match();
};

#endif
