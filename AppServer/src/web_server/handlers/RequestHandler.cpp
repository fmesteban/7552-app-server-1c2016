#include "RequestHandler.h"


RequestHandler::RequestHandler(const std::string _uri):
uri(_uri){
}


const std::string& RequestHandler::getUri(){
	return uri;
}


RequestHandler::~RequestHandler(){ }
