#ifndef WEB_SERVER_HANDLERS_REQUESTHANDLER_H_
#define WEB_SERVER_HANDLERS_REQUESTHANDLER_H_

#include "mongoose.h"
#include <string>
#include <json/json.h>

class RequestHandler {
protected:
	const std::string uri;
public:
	RequestHandler(const std::string _uri);
	virtual void run(struct mg_connection *networkConnection, mg_str *body) = 0;
	const std::string& getUri();
	virtual ~RequestHandler();
};

#endif
