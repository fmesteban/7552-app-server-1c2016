#ifndef WEB_CLIENT_WEBCLIENT_H_
#define WEB_CLIENT_WEBCLIENT_H_

#include <string>
#include "mongoose.h"
#include "Response.h"
#include "Request.h"
#include "log.h"

class WebClient{
private:
	struct mg_mgr mgr;
	int keepAlive;
	std::string remoteHost;
	void insertDefaultHeaders(Request &request);
public:
	WebClient();
	std::pair<int, int> sendRegister(const std::string& data);
	std::string sendLogin(const std::string& userID);
	void eventHandler(struct mg_connection *nc, int ev, void *ev_data);
	bool sendEditProfile(const std::string& putData, const std::string &userID);
	~WebClient();
};

#endif
