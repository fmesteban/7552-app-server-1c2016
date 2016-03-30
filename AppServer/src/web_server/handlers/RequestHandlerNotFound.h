#ifndef WEB_SERVER_HANDLERS_REQUESTHANDLERNOTFOUND_H_
#define WEB_SERVER_HANDLERS_REQUESTHANDLERNOTFOUND_H_


#include "RequestHandler.h"


class RequestHandlerNotFound: public RequestHandler {
public:
	RequestHandlerNotFound();
	void run(struct mg_connection *networkConnection, mg_str *body);
};


#endif
