#ifndef WEB_SERVER_HANDLERS_REQUESTHANDLER_H_
#define WEB_SERVER_HANDLERS_REQUESTHANDLER_H_

#include "mongoose.h"
#include <string>
#include <json/json.h>

#define STRING_FROM_FIELD( fieldName )                                              \
	char fieldName ## Buf[ 256 ] = { 0 };                                           \
	mg_get_http_var(body, #fieldName, fieldName ## Buf, sizeof(fieldName ## Buf));  \
	std::string fieldName(fieldName ## Buf);


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
