#ifndef WEB_SERVER_RESPONSE_H_
#define WEB_SERVER_RESPONSE_H_

#include <map>
#include <string>
#include "mongoose.h"
#include <iostream>

typedef int httpStatus;
#define UNDEFINED_STATUS -1

class Response {
private:
	std::string body;
	httpStatus status;
public:
	Response();
	void parseMessage(struct http_message &httpMessage);
	std::string &getBody();
	httpStatus getStatus();
};

#endif
