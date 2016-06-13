#ifndef WEB_SERVER_HANDLERS_REQUESTHANDLERCONVERSATION_H_
#define WEB_SERVER_HANDLERS_REQUESTHANDLERCONVERSATION_H_

#include "RequestHandler.h"
#include "UsersContainer.h"
#include <string>
#include "log.h"

class RequestHandlerConversation: public RequestHandler {
private:
	UsersContainer &users;
public:
	explicit RequestHandlerConversation(UsersContainer &users);
	void run(Request &request);
};

#endif
