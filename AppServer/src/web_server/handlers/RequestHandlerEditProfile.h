#ifndef WEB_SERVER_HANDLERS_REQUESTHANDLEREDITPROFILE_H_
#define WEB_SERVER_HANDLERS_REQUESTHANDLEREDITPROFILE_H_

#include "RequestHandler.h"
#include "UsersContainer.h"
#include "log.h"
#include <string>

class RequestHandlerEditProfile: public RequestHandler {
private:
	UsersContainer &users;
public:
	explicit RequestHandlerEditProfile(UsersContainer &users);
	void run(Request &request);
};

#endif
