#include "ChatMessage.h"

ChatMessage::ChatMessage(User &userSrc, const std::string &message) :
	userSrc(userSrc),
	message(message){
}

