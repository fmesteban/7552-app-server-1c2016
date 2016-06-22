#ifndef WEB_SERVER_MATCHER_CHAT_H_
#define WEB_SERVER_MATCHER_CHAT_H_

#include <vector>
#include <string>
#include "ChatMessage.h"
#include "User.h"

class Chat {
private:
	User &userA;
	User &userB;
	std::vector<ChatMessage*> messagesFromA;
	std::vector<ChatMessage*> messagesFromB;
	void printMessages(std::ostream &os, const std::vector<ChatMessage*> &messages) const;
	void clearMessages(std::vector<ChatMessage*> &messages);
public:
	Chat(User &userA, User &userB);
	void pushMessage(User &userSrc, const std::string &message, const std::string &time);
	friend std::ostream &operator<<(std::ostream &os, const Chat& self);
	void printTo(std::ostream &os, User &userSrc);
	~Chat();
};

#endif
