#include "RequestManager.h"
#include <utility>
#include <map>
#include <string>

RequestManager::RequestManager(UsersContainer &users, SuggestionsGenerator &suggestionsGenerator) :
	users(users),
	reqRegister(users),
	reqLogin(users),
	reqEditProfile(users),
	reqPossibleMatches(users, suggestionsGenerator),
	reqMatches(users),
	reqGetConversation(users),
	reqSendConversation(users),
	reqLike(users),
	reqDislike(users) {
	insertDefaultHandlers();
}

/** Associates the RequestHandlers with theirs URI.
 */
void RequestManager::insertDefaultHandlers(){
	addHandler(reqRegister.getUri(), &reqRegister);
	addHandler(reqLogin.getUri(), &reqLogin);
	addHandler(reqEditProfile.getUri(), &reqEditProfile);
	addHandler(reqPossibleMatches.getUri(), &reqPossibleMatches);
	addHandler(reqMatches.getUri(), &reqMatches);
	addHandler(reqGetConversation.getUri(), &reqGetConversation);
	addHandler(reqSendConversation.getUri(), &reqSendConversation);
	addHandler(reqLike.getUri(), &reqLike);
	addHandler(reqDislike.getUri(), &reqDislike);
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

