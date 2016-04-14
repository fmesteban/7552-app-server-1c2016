#ifndef WEB_SERVER_REQUESTMANAGER_H_
#define WEB_SERVER_REQUESTMANAGER_H_

#include <map>
#include "Database.h"
#include "RequestHandler.h"
#include "RequestHandlerExample.h"
#include "RequestHandlerNotFound.h"
#include "RequestHandlerRegister.h"

class RequestManager {
private:
	Database db;
	std::map<std::string, RequestHandler*> handlerRefs;
	RequestHandlerExample reqExample;
	RequestHandlerNotFound hdlNotFound;
	RequestHandlerRegister reqRegister;
	void insertDefaultHandlers();
public:
	RequestManager();
	void addHandler(const std::string& uri, RequestHandler* reqHandler);
	RequestHandler* getHanlder(const std::string& uri);
};

#endif
