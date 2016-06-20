#ifndef WEB_SERVER_REQUESTMANAGER_H_
#define WEB_SERVER_REQUESTMANAGER_H_

#include <handlers/RequestHandlerGetConversation.h>
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
#include "RequestHandlerGetConversation.h"
#include "RequestHandlerSendConversation.h"
#include "RequestHandlerLike.h"
#include "RequestHandlerDislike.h"

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
	RequestHandlerMatches reqMatches;
	RequestHandlerGetConversation reqGetConversation;
	RequestHandlerSendConversation reqSendConversation;
	RequestHandlerLike reqLike;
	RequestHandlerDislike reqDislike;
	void insertDefaultHandlers();
public:
	explicit RequestManager(UsersContainer &users, SuggestionsGenerator &suggestionsGenerator);
	void addHandler(const std::string& uri, RequestHandler* reqHandler);
	RequestHandler& getHanlder(const std::string& uri);
};

#endif
