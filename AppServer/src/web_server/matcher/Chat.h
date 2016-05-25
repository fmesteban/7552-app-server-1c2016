#ifndef WEB_SERVER_MATCHER_CHAT_H_
#define WEB_SERVER_MATCHER_CHAT_H_

#include <vector>
#include "ChatMessage.h"

class Chat {
private:
	std::vector<ChatMessage*> messages;
public:
	Chat();
	~Chat();
};

#endif
