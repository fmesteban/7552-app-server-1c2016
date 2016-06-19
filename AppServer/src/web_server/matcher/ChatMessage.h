#ifndef WEB_SERVER_MATCHER_CHATMESSAGE_H_
#define WEB_SERVER_MATCHER_CHATMESSAGE_H_

#include <string>
#include "User.h"

class ChatMessage {
private:
	User &userSrc;
	std::string message;
public:
	ChatMessage(User &userSrc, const std::string &message);
};

#endif
