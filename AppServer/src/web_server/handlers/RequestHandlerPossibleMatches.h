#ifndef WEB_SERVER_HANDLERS_REQUESTHANDLERPOSSIBLEMATCHES_H_
#define WEB_SERVER_HANDLERS_REQUESTHANDLERPOSSIBLEMATCHES_H_

#include "RequestHandler.h"
#include "UsersContainer.h"
#include "SuggestionsGenerator.h"
#include <string>
#include "log.h"

class RequestHandlerPossibleMatches: public RequestHandler {
private:
	UsersContainer &users;
public:
	explicit RequestHandlerPossibleMatches(UsersContainer &users);
	void run(Request &request);
};

#endif
