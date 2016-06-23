/** Include area. */
#include "Chat.h"
#include <vector>

Chat::Chat(User &userA, User &userB) :
userA(userA),
userB(userB){
}

void Chat::pushMessage(User &userSrc, const std::string &message, const std::string &time){
	if(userSrc == userA)
		messagesFromA.push_back(new ChatMessage(userSrc, message, time));
	else
		messagesFromB.push_back(new ChatMessage(userSrc, message, time));
}

void Chat::printMessages(std::ostream &os, const std::vector<ChatMessage*> &messages) const{
	if (!messages.empty()){
		for (size_t i=0; i < messages.size() - 1; ++i){
			/* with comma */
			os << *messages[i] << ",";
		}
		/* without comma */
		os << *messages[messages.size() - 1];
	}
}

void Chat::clearMessages(std::vector<ChatMessage*> &messages){
	for (size_t i=0; i < messages.size(); ++i)
		delete messages[i];
	messages.clear();
}


void Chat::printTo(std::ostream &os, User &userSrc){
	os << "[";

	if(userSrc == userA){
		printMessages(os, messagesFromA);
		clearMessages(messagesFromA);
	}else{
		printMessages(os, messagesFromB);
		clearMessages(messagesFromB);
	}

	os << "]";
}

/** Overloads the operator << from std::ostream
 *
 */
std::ostream& operator<<(std::ostream &os, const Chat& self) {
	os << "[";

	bool commaInTheMiddle = (self.messagesFromA.size() > 0) && (self.messagesFromB.size() > 0);
	self.printMessages(os, self.messagesFromA);
	if(commaInTheMiddle) os << ", ";
	self.printMessages(os, self.messagesFromB);

	return os << "]";
}


Chat::~Chat() {
	clearMessages(messagesFromA);
	clearMessages(messagesFromB);
}

