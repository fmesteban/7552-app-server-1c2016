#ifndef WEB_SERVER_HANDLERS_REQUESTHANDLERLOGIN_H_
#define WEB_SERVER_HANDLERS_REQUESTHANDLERLOGIN_H_

#include "RequestHandler.h"
#include "UsersContainer.h"
#include "log.h"
#include <string>

class RequestHandlerLogin: public RequestHandler {
private:
	UsersContainer &users;
public:
	explicit RequestHandlerLogin(UsersContainer &users);
	void run(Request &request);
};

#endif
