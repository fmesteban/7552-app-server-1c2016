#include "ChatMessage.h"

ChatMessage::ChatMessage(User &userSrc, const std::string &message, const std::string &time) :
	userSrc(userSrc),
	message(message),
	time(time){
}

/** Overloads the operator << from std::ostream
 *
 */
std::ostream& operator<<(std::ostream &os, const ChatMessage& self) {
	return os <<
			"{" <<
				"\"sendFrom\": \"" << self.userSrc.getEmail() << "\"," <<
				"\"msg\": \"" << self.message << "\"," <<
				"\"time\": \"" << self.time << "\"" <<
			"}";
}