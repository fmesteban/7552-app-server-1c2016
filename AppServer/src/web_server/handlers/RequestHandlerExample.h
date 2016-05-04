#ifndef WEB_SERVER_HANDLERS_REQUESTHANDLEREXAMPLE_H_
#define WEB_SERVER_HANDLERS_REQUESTHANDLEREXAMPLE_H_


#include "RequestHandler.h"


class RequestHandlerExample: public RequestHandler {
public:
	RequestHandlerExample();
	void run(Request &request);
};


#endif
