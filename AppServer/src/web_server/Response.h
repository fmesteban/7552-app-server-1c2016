#ifndef WEB_SERVER_RESPONSE_H_
#define WEB_SERVER_RESPONSE_H_

#include <map>
#include <string>
#include "mongoose.h"
#include <iostream>

typedef int httpStatus;
#define UNDEFINED_STATUS -1
#define BAD_REQUEST_STATUS 400
#define SERVER_ERROR_STATUS 500 
#define OK_STATUS 200
#define ACCEPTED_STATUS 201

#define BAD_REQUEST_MSG "Bad Request"
#define SERVER_ERROR_MSG "Internal Server Error"
#define OK_MSG "OK"
#define ACCEPTED_MSG "Accepted"


class Response {
protected:
	std::string body;
	httpStatus status;
public:
	Response();
	Response(httpStatus status, std::string msg);
	void parseMessage(struct http_message &httpMessage);
	std::string &getBody();
	httpStatus getStatus();
};

#endif
