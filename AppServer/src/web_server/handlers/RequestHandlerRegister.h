#ifndef WEB_SERVER_HANDLERS_REQUESTHANDLERREGISTER_H_
#define WEB_SERVER_HANDLERS_REQUESTHANDLERREGISTER_H_


#include "RequestHandler.h"


class RequestHandlerRegister: public RequestHandler {
public:
	RequestHandlerRegister();
	void run(struct mg_connection *networkConnection, mg_str *body);
};


#endif
