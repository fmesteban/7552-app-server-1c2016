#ifndef WEB_SERVER_MATCHER_CHAT_H_
#define WEB_SERVER_MATCHER_CHAT_H_

#include <vector>
#include <string>
#include "ChatMessage.h"

class Chat {
private:
	std::vector<ChatMessage*> messages;
public:
	Chat();
	void pushMessage(User &userSrc, const std::string &message, const std::string &time);
	friend std::ostream & operator<<(std::ostream &os, const Chat& self);
	~Chat();
};

#endif
