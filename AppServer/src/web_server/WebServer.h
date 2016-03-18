#ifndef WEBSERVER_H_
#define WEBSERVER_H_

#include "mongoose.h"
#include <string>

class WebServer {
private:
	const std::string httpPort;
	struct mg_mgr eventManager;
	struct mg_connection *networkConnection;
public:
	struct mg_serve_http_opts s_http_server_opts;
	int is_websocket(const struct mg_connection *nc);
	void broadcast(struct mg_connection *nc, const char *msg, size_t len);

	WebServer();
	void start();
	~WebServer();
};

#endif
