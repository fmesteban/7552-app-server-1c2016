#include "RequestManager.h"


RequestManager::RequestManager() {
	insertDefaultHandlers();
}

/** Associates the RequestHandlers with theirs URI.
 */
void RequestManager::insertDefaultHandlers(){
	addHandler(reqExample.getUri(), &reqExample);
}


void RequestManager::addHandler(const std::string& uri, RequestHandler* reqHandler){
	handlerRefs.insert(std::pair<std::string,RequestHandler*>(uri,reqHandler));
}



/**TODO: cambiar para devolver referencia, pero ojo porque asi no podria
 * devolver null
 */
RequestHandler* RequestManager::getHanlder(const std::string& uri){
	std::map<std::string, RequestHandler*>::iterator hdlr = handlerRefs.find(uri);
	if (hdlr != handlerRefs.end() )
		return (hdlr->second);
	else
		return &hdlNotFound;
}

