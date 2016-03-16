#ifndef WEBSERVER_H_
#define WEBSERVER_H_

#include "mongoose.h"
#include <string>

class WebServer {
private:
	const std::string httpPort;
	struct mg_mgr eventManager;
	struct mg_connection *networkConnection;
	static void eventHandler( struct mg_connection *nc, int ev, void *p );
	static int is_websocket(const struct mg_connection *nc);
	static void broadcast(struct mg_connection *nc, const char *msg, size_t len);
public:
	WebServer();
	void start();
	~WebServer();
};

#endif
