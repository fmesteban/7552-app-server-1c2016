/** Include area. */
#include "Chat.h"
#include <vector>
#include <string>


/*------------------------------------------------------------------------
 * 	Member Functions Implementations
 * ---------------------------------------------------------------------*/

/** Chat constructor.
 *
 *	\param userA Is one user on the conversation.
 *	\param userB Is the other user.
 */
Chat::Chat(User &userA, User &userB) :
userA(userA),
userB(userB){
}


/** Adds a message to the conversation.
 *
 *  \param userSrc Is the user who sent the message.
 *  \param message Is the message as string.
 *  \param time Is a timestamp as string.
 */
void Chat::pushMessage(
	User &userSrc, 
	const std::string &message, 
	const std::string &time){
	if(userSrc == userA)
		messagesFromA.push_back(new ChatMessage(userSrc, message, time));
	else
		messagesFromB.push_back(new ChatMessage(userSrc, message, time));
}


/**	Prints the messages as a list, separating chat messages with commas.
 *
 *	\param os Is the output stream where the chat messages will be printed.
 *	\param messages Is the array of messages to print.
 */
void Chat::printMessages(
	std::ostream &os, 
	const std::vector<ChatMessage*> &messages) const{
	if (!messages.empty()){
		for (size_t i=0; i < messages.size() - 1; ++i){
			/* with comma */
			os << *messages[i] << ",";
		}
		/* without comma */
		os << *messages[messages.size() - 1];
	}
}


/** Releases all messages in an array.
 *
 *	\param messages Is the array to be cleared.
 */
void Chat::clearMessages(std::vector<ChatMessage*> &messages){
	for (size_t i=0; i < messages.size(); ++i)
		delete messages[i];
	messages.clear();
}


/** Prints the messages from a specified user.
 *
 * 	\param os Is the output stream where the chat messages will be printed.
 * 	\param userSrc Is the user who sent the messages what will be printed.
 */
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
 *	\param os Is the output stream.
 *	\param self Is the current instance of Chat to be printed.
 */
std::ostream& operator<<(std::ostream &os, const Chat& self) {
	os << "[";

	bool commaInTheMiddle = 
		(self.messagesFromA.size() > 0) && 
		(self.messagesFromB.size() > 0);
	self.printMessages(os, self.messagesFromA);
	if(commaInTheMiddle) os << ", ";
	self.printMessages(os, self.messagesFromB);

	return os << "]";
}


/** Releases the memory reserved by Chat.
 *
 */
Chat::~Chat() {
	clearMessages(messagesFromA);
	clearMessages(messagesFromB);
}

