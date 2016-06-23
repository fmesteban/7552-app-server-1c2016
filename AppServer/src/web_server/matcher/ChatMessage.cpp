/** Include area. */
#include "ChatMessage.h"
#include <string>


/*------------------------------------------------------------------------
 * 	Member Functions Implementations
 * ---------------------------------------------------------------------*/

/** Chat message constructor.
 *
 * 	\param userSrc Is a refference to user who sent the message.
 * 	\param message Is the message as string.
 * 	\param time Is a string representing a timestamp.
 */
ChatMessage::ChatMessage(
		User &userSrc, 
		const std::string &message, 
		const std::string &time) :
	userSrc(userSrc),
	message(message),
	time(time){
}

/** Overloads the operator << from std::ostream
 *
 *	\param os Is the output stream.
 *	\param self Is the current chat message what will be printed.
 */
std::ostream& operator<<(std::ostream &os, const ChatMessage& self) {
	return os <<
			"{" <<
				"\"sendFrom\": \"" << self.userSrc.getEmail() << "\"," <<
				"\"msg\": \"" << self.message << "\"," <<
				"\"time\": \"" << self.time << "\"" <<
			"}";
}
