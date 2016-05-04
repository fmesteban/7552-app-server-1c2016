#ifndef WEB_SERVER_HANDLERS_REQUESTHANDLER_H_
#define WEB_SERVER_HANDLERS_REQUESTHANDLER_H_

#include "mongoose.h"
#include <string>
#include <json/json.h>
#include "Request.h"

class RequestHandler {
protected:
	const std::string uri;
	void sendHttpOk(struct mg_connection *nc, const std::string &extraLine);
public:
	explicit RequestHandler(const std::string _uri);
	virtual void run(Request &request) = 0;
	const std::string& getUri();
	virtual ~RequestHandler();
};

#endif
