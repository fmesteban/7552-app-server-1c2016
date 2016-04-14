#ifndef WEB_SERVER_HANDLERS_REQUESTHANDLERREGISTER_H_
#define WEB_SERVER_HANDLERS_REQUESTHANDLERREGISTER_H_


#include "RequestHandler.h"
#include "Database.h"

class RequestHandlerRegister: public RequestHandler {
private:
	Database &db;
	void sendHttpOk(struct mg_connection *nc, const std::string& response);
public:
	RequestHandlerRegister(Database& db);
	void run(struct mg_connection *networkConnection, mg_str *body);
};


#endif
