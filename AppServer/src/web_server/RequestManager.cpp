#include "RequestManager.h"
#include <utility>
#include <map>
#include <string>


RequestManager::RequestManager(UsersContainer &users) :
	users(users),
	reqRegister(users),
	reqLogin(users),
	reqEditProfile(users),
	reqPossibleMatches(users),
	reqMatches(users),
	reqConversation(users) {
	insertDefaultHandlers();
}


/** Associates the RequestHandlers with theirs URI.
 */
void RequestManager::insertDefaultHandlers(){
	addHandler(reqExample.getUri(), &reqExample);
	addHandler(reqRegister.getUri(), &reqRegister);
	addHandler(reqLogin.getUri(), &reqLogin);
	addHandler(reqEditProfile.getUri(), &reqEditProfile);
	addHandler(reqPossibleMatches.getUri(), &reqPossibleMatches);
	addHandler(reqMatches.getUri(), &reqMatches);
	addHandler(reqConversation.getUri(), &reqConversation);
}


/**	Adds a individual handler to hdlrs list.
 *
 */
void RequestManager::addHandler(
		const std::string& uri,
		RequestHandler* reqHandler){
	handlerRefs.insert(std::pair<std::string,RequestHandler*>(uri,reqHandler));
}


/** Gets the handler corresponding to passed uri.
 *
 */
RequestHandler& RequestManager::getHanlder(const std::string& uri){
	std::map<std::string, RequestHandler*>::iterator hdlr = handlerRefs.find(uri);
	if (hdlr != handlerRefs.end() )
		return *(hdlr->second);
	else
		return hdlNotFound;
}

