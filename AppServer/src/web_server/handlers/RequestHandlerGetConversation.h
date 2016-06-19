#ifndef WEB_SERVER_HANDLERS_REQUESTHANDLERGETCONVERSATION_H_
#define WEB_SERVER_HANDLERS_REQUESTHANDLERGETCONVERSATION_H_

#include "RequestHandler.h"
#include "UsersContainer.h"
#include <string>
#include "log.h"

class RequestHandlerGetConversation: public RequestHandler {
private:
	UsersContainer &users;
public:
	explicit RequestHandlerGetConversation(UsersContainer &users);
	void run(Request &request);
};

#endif
