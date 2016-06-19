#include "Chat.h"
#include <vector>

Chat::Chat() {
}

void Chat::pushMessage(User &userSrc, const std::string &message){
	messages.push_back(new ChatMessage(userSrc, message));
}

Chat::~Chat() {
	std::vector<ChatMessage*>::iterator iter = messages.begin();
	for(; iter != messages.end(); ++iter){
		delete *iter;
	}
}

