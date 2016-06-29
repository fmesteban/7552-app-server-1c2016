#ifndef WEB_SERVER_HANDLERS_REQUESTHANDLERCHECKTOKEN_H_
#define WEB_SERVER_HANDLERS_REQUESTHANDLERCHECKTOKEN_H_

/** Include area. */
#include "RequestHandler.h"
#include "UsersContainer.h"
#include <string>

class RequestHandlerCheckToken: public RequestHandler {
private:
	UsersContainer &users;
public:
	explicit RequestHandlerCheckToken(UsersContainer &users);
	void run(Request &request);
};

#endif
