#ifndef WEB_SERVER_HANDLERS_REQUESTHANDLERREGISTER_H_
#define WEB_SERVER_HANDLERS_REQUESTHANDLERREGISTER_H_

#include "RequestHandler.h"
#include "UsersContainer.h"
#include <string>
#include "log.h"

class RequestHandlerRegister: public RequestHandler {
private:
	UsersContainer &users;
public:
	explicit RequestHandlerRegister(UsersContainer &users);
	void run(Request &request);
};

#endif
