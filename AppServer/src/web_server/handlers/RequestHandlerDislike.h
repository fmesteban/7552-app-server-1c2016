#ifndef WEB_SERVER_HANDLERS_REQUESTHANDLERDISLIKE_H_
#define WEB_SERVER_HANDLERS_REQUESTHANDLERDISLIKE_H_

#include "RequestHandler.h"
#include "UsersContainer.h"
#include "SuggestionsGenerator.h"
#include <string>
#include "log.h"

class RequestHandlerDislike: public RequestHandler {
private:
	UsersContainer &users;
public:
	explicit RequestHandlerDislike(UsersContainer &users);
	void run(Request &request);
};

#endif
