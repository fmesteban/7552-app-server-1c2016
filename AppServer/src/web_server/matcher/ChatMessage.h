#ifndef WEB_SERVER_MATCHER_CHATMESSAGE_H_
#define WEB_SERVER_MATCHER_CHATMESSAGE_H_

#include <string>
#include "User.h"

class ChatMessage {
private:
	User &userSrc;
	std::string message;
	std::string time;
public:
	ChatMessage(User &userSrc, const std::string &message, const std::string &time);
	friend std::ostream & operator<<(std::ostream &os, const ChatMessage& self);
};

#endif
