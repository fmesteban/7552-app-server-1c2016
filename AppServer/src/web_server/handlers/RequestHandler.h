#ifndef WEB_SERVER_HANDLERS_REQUESTHANDLER_H_
#define WEB_SERVER_HANDLERS_REQUESTHANDLER_H_

#include "mongoose.h"
#include <string>
#include <json/json.h>

#define INIT_JSON \
	std::string payload(std::string(body->p).substr(0, body->len)); \
	Json::Value root; \
	Json::Reader reader; \
	bool parsingSuccessful = reader.parse(payload, root); \
	if(!parsingSuccessful){ \
		/* malformed json data */ \
	}

#define STRING_FROM_FIELD(fieldName)     		\
	std::string fieldName = root.get(#fieldName, "unavailable field").asString();

class RequestHandler {
protected:
	const std::string uri;
	void sendHttpOk(struct mg_connection *nc, const std::string &extraLine);
public:
	explicit RequestHandler(const std::string _uri);
	virtual void run(struct mg_connection *networkConnection, mg_str *body) = 0;
	const std::string& getUri();
	virtual ~RequestHandler();
};

#endif
