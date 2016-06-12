#include "Chat.h"
#include <vector>

Chat::Chat() {
}

Chat::~Chat() {
	std::vector<ChatMessage*>::iterator iter = messages.begin();
	for(; iter != messages.end(); ++iter){
		delete *iter;
	}
}

