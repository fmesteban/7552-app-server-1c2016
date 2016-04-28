#ifndef WEB_CLIENT_WEBCLIENT_H_
#define WEB_CLIENT_WEBCLIENT_H_

#include <string>
#include "mongoose.h"

class WebClient {
private:
	struct mg_mgr mgr;
	int keepAlive;
	bool s_show_headers;
public:
	WebClient();
	void sendRegister(const std::string& data);
    void sendLogin(const std::string& data);
	void eventHandler(struct mg_connection *nc, int ev, void *ev_data);
	~WebClient();
};

#endif
