/** Include area. */
#include "Match.h"


/*------------------------------------------------------------------------
 * 	Member Functions Implementations
 * ---------------------------------------------------------------------*/

/** Match constructor.
 *
 * 	\param userA Is one of the two users who matched.
 * 	\param userB Is the other.
 */
Match::Match(User &userA, User &userB) :
	userA(userA),
	userB(userB),
	chat(userA, userB) {
}


/** Gets a refference to one of the users of the match.
 *
 *	\return The refference to one of the users of the match.
 */
User &Match::getUserA(){
	return userA;
}


/** Gets a refference to one of the users of the match (not eq getUserA).
 *
 *	\return The refference to one of the users of the match.
 */
User &Match::getUserB(){
	return userB;
}


/** Adds a message to the conversation of the match.
 *
 *	\param userStc Is the user who sent the message.
 *	\param message Is the message as string.
 *	\param Is the timestamp represented as string.
 */
void Match::pushChatMessage(User &userSrc, const std::string &message, const std::string &time){
	chat.pushMessage(userSrc, message, time);
}


/** Gets the conversation from the match.
 *
 *	\return A chat refference.
 */
Chat &Match::getChat(){
	return chat;
}

/** Overloads the operator << from std::ostream
 *
 *	\param os Is the output stream.
 *	\param self Is the current match instance.
 */
std::ostream& operator<<(std::ostream &os, const Match& self) {
	return os <<
		"{"
			"\"userA\":\"" << self.userA.getID() << "\","
			"\"userB\":\"" << self.userB.getID() << "\","
			"\"chat\":" << self.chat <<
		"}";
}


Match::~Match() {
}
