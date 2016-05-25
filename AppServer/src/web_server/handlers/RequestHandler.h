#ifndef WEB_SERVER_HANDLERS_REQUESTHANDLER_H_
#define WEB_SERVER_HANDLERS_REQUESTHANDLER_H_

#include "mongoose.h"
#include <string>
#include <json/json.h>
#include "log.h"
#include "Request.h"
#include "Response.h"

class RequestHandler {
protected:
	const std::string uri;
	void sendHttpOk(struct mg_connection *nc, const std::string &extraLine);
	void sendResponse(Response &r, struct mg_connection *nc);
public:
	explicit RequestHandler(const std::string _uri);
	virtual void run(Request &request) = 0;
	const std::string& getUri();
	virtual ~RequestHandler();
};

#endif
