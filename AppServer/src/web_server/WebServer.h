#ifndef WEBSERVER_H_
#define WEBSERVER_H_

/** Include area. */
#include "mongoose.h"
#include <string>
#include "RequestManager.h"
#include "Thread.h"
#include "log.h"
#include "SuggestionsGenerator.h"

class WebServer : public Thread{
private:
	const std::string httpPort;
	struct mg_mgr eventManager;
	struct mg_connection *networkConnection;
	UsersContainer users;
	SuggestionsGenerator suggestionsGenerator;
	RequestManager requestManager;
	static void eventHandler(struct mg_connection *networkConnection,
			int eventCode, void *dataPointer);
	bool keepAlive;

public:
	struct mg_serve_http_opts serverOptions;
	void handleRequest(Request &request);
	explicit WebServer(const std::string &port);
	void run();
	void stop();
	virtual ~WebServer();
};

#endif
