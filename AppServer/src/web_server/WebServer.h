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
	RequestManager requestManager;
	static void eventHandler(struct mg_connection *nc, int ev, void *p);

public:
	struct mg_serve_http_opts s_http_server_opts;
	void handleURI(struct mg_connection *networkConnection,
					const std::string& uri,
					mg_str *body);
	WebServer();
	void start();
	virtual ~WebServer();
};

#endif
