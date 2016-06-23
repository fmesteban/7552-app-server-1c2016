#ifndef WEB_SERVER_HANDLERS_REQUESTHANDLERPOSSIBLEMATCHES_H_
#define WEB_SERVER_HANDLERS_REQUESTHANDLERPOSSIBLEMATCHES_H_

/** Include area. */
#include "RequestHandler.h"
#include "UsersContainer.h"
#include "SuggestionsGenerator.h"
#include <string>
#include "log.h"

class RequestHandlerPossibleMatches: public RequestHandler {
private:
	UsersContainer &users;
	SuggestionsGenerator &suggestionsGenerator;
public:
	explicit RequestHandlerPossibleMatches(
		UsersContainer &users, 
		SuggestionsGenerator &suggestionsGenerator);
	void run(Request &request);
};

#endif
