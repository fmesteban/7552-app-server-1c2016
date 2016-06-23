#ifndef WEB_SERVER_HANDLERS_REQUESTHANDLERMATCHES_H_
#define WEB_SERVER_HANDLERS_REQUESTHANDLERMATCHES_H_

/** Include area. */
#include "RequestHandler.h"
#include "UsersContainer.h"
#include "SuggestionsGenerator.h"
#include <string>
#include "log.h"

class RequestHandlerMatches: public RequestHandler {
private:
	UsersContainer &users;
public:
	explicit RequestHandlerMatches(UsersContainer &users);
	void run(Request &request);
};

#endif
