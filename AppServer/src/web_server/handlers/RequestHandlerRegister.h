#ifndef WEB_SERVER_HANDLERS_REQUESTHANDLERREGISTER_H_
#define WEB_SERVER_HANDLERS_REQUESTHANDLERREGISTER_H_

#include "RequestHandler.h"
#include "UsersContainer.h"
#include <string>

class RequestHandlerRegister: public RequestHandler {
private:
	UsersContainer &users;
public:
	explicit RequestHandlerRegister(UsersContainer &users);
	void run(struct mg_connection *networkConnection, mg_str *body);
};

#endif
