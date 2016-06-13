#ifndef WEB_SERVER_REQUESTMANAGER_H_
#define WEB_SERVER_REQUESTMANAGER_H_

#include <map>
#include <string>
#include "UsersContainer.h"
#include "RequestHandler.h"
#include "RequestHandlerExample.h"
#include "RequestHandlerNotFound.h"
#include "RequestHandlerRegister.h"
#include "RequestHandlerLogin.h"
#include "RequestHandlerEditProfile.h"
#include "RequestHandlerPossibleMatches.h"
#include "RequestHandlerMatches.h"
#include "RequestHandlerConversation.h"

class RequestManager {
private:
	UsersContainer &users;
	std::map<std::string, RequestHandler*> handlerRefs;
	RequestHandlerExample reqExample;
	RequestHandlerNotFound hdlNotFound;
	RequestHandlerRegister reqRegister;
	RequestHandlerLogin reqLogin;
	RequestHandlerEditProfile reqEditProfile;
	RequestHandlerPossibleMatches reqPossibleMatches;
	RequestHandlerreqMatches reqMatches;
	RequestHandlerConversation reqConversacion;
	void insertDefaultHandlers();
public:
	explicit RequestManager(UsersContainer &users);
	void addHandler(const std::string& uri, RequestHandler* reqHandler);
	RequestHandler& getHanlder(const std::string& uri);
};

#endif
