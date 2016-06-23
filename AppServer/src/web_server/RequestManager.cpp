/** Include area. */
#include "RequestManager.h"
#include <utility>
#include <map>
#include <string>


/*------------------------------------------------------------------------
 * 	Member Functions Implementations
 * ---------------------------------------------------------------------*/

/** Request manager constructor. Contains the request handlers.
 *
 *	\param users Is a refference to the server users container.
 *	\param suggestionsGenerator Is a refference to the suggestions generator.
 */
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

/** Associates the RequestHandlers with their URIs.
 *
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
 *	\param uri Is the uri to be handled by handler.
 *	\param reqHandler Is the object that handles the \uri.
 */
void RequestManager::addHandler(
		const std::string& uri,
		RequestHandler* reqHandler){
	handlerRefs.insert(std::pair<std::string,RequestHandler*>(uri,reqHandler));
}


/** Gets the handler corresponding to passed uri.
 *
 *	\param uri Is the uri to be handled.
 *
 *	\return The corresponding request handler refference if it is added
 *	to map, or a handler of not found requests otherwise.
 */
RequestHandler& RequestManager::getHanlder(const std::string& uri){
	std::map<std::string, RequestHandler*>::iterator hdlr = handlerRefs.find(uri);
	if (hdlr != handlerRefs.end() )
		return *(hdlr->second);
	else
		return hdlNotFound;
}
