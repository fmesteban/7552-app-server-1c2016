#ifndef WEBSERVER_H_
#define WEBSERVER_H_

#include "mongoose.h"
#include <string>
#include "RequestManager.h"

class WebServer {
private:
	const std::string httpPort;
	struct mg_mgr eventManager;
	struct mg_connection *networkConnection;
	UsersContainer users;
	RequestManager requestManager;
	static void eventHandler(struct mg_connection *networkConnection,
			int eventCode, void *dataPointer);

public:
	struct mg_serve_http_opts serverOptions;
	void handleURI(struct mg_connection *networkConnection,
					const std::string& uri,
					mg_str *body);
	WebServer();
	void start();
	virtual ~WebServer();
};

#endif
