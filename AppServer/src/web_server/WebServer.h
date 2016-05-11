#ifndef WEBSERVER_H_
#define WEBSERVER_H_

#include "mongoose.h"
#include <string>
#include "RequestManager.h"
#include "Thread.h"

class WebServer : public Thread{
private:
	const std::string httpPort;
	struct mg_mgr eventManager;
	struct mg_connection *networkConnection;
	UsersContainer users;
	RequestManager requestManager;
	static void eventHandler(struct mg_connection *networkConnection,
			int eventCode, void *dataPointer);
	bool keepAlive;

public:
	struct mg_serve_http_opts serverOptions;
	void handleRequest(Request &request);
	WebServer();
	void run();
	void stop();
	virtual ~WebServer();
};

#endif
