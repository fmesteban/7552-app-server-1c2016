#ifndef WEB_SERVER_HANDLERS_REQUESTHANDLERSENDCONVERSATION_H_
#define WEB_SERVER_HANDLERS_REQUESTHANDLERSENDCONVERSATION_H_

#include "RequestHandler.h"
#include "UsersContainer.h"
#include <string>
#include "log.h"

class RequestHandlerSendConversation: public RequestHandler {
private:
	UsersContainer &users;
public:
	explicit RequestHandlerSendConversation(UsersContainer &users);
	void run(Request &request);
};

#endif
