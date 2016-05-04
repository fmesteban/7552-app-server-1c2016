#ifndef WEB_SERVER_HANDLERS_REQUESTHANDLERLOGIN_H_
#define WEB_SERVER_HANDLERS_REQUESTHANDLERLOGIN_H_

#include "RequestHandler.h"
#include "UsersContainer.h"
#include <string>

class RequestHandlerLogin: public RequestHandler {
private:
	UsersContainer &users;
public:
	explicit RequestHandlerLogin(UsersContainer &users);
	void run(struct mg_connection *networkConnection, mg_str *body);
	void run(Request &request);
};

#endif
