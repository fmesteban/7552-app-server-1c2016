#include "Chat.h"
#include <vector>

Chat::Chat() {
}

void Chat::pushMessage(User &userSrc, const std::string &message, const std::string &time){
	messages.push_back(new ChatMessage(userSrc, message, time));
}

/** Overloads the operator << from std::ostream
 *
 */
std::ostream& operator<<(std::ostream &os, const Chat& self) {
	os << "\"messages\": [ ";

	if (!self.messages.empty()){
		for (size_t i=0; i < self.messages.size() - 1; ++i){
			/* with comma */
			os << *self.messages[i] << ",";
		}
		/* without comma */
		os << *self.messages[self.messages.size() - 1];
	}

	return os << "]";
}

/** Overloads the operator << from std::ostream
 *
 */
std::ostream& operator<<(std::ostream &os, const Chat& self) {
	os << "\"messages\":[";
	if(!messages.isEmpty()){
		for (size_t i=0; i < messages.size() - 1; ++i){
			/* with comma */
			os << *messages[i] << ",";
		}
		/* without comma */
		os << *messages[messages.size() - 1];
	}
	os << "]";
	return os;
}

Chat::~Chat() {
	std::vector<ChatMessage*>::iterator iter = messages.begin();
	for(; iter != messages.end(); ++iter){
		delete *iter;
	}
}

