#ifndef WEB_SERVER_HANDLERS_REQUESTHANDLERLIKE_H_
#define WEB_SERVER_HANDLERS_REQUESTHANDLERLIKE_H_

/** Include area. */
#include "RequestHandler.h"
#include "UsersContainer.h"
#include "SuggestionsGenerator.h"
#include <string>
#include "log.h"

class RequestHandlerLike: public RequestHandler {
private:
	UsersContainer &users;
public:
	explicit RequestHandlerLike(UsersContainer &users);
	void run(Request &request);
};

#endif
