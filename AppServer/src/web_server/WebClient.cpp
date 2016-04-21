#include "WebClient.h"
#include <iostream>
#include <string>


#define WEB_CLIENT_LOG 1

static void ev_handler(struct mg_connection *nc, int ev, void *ev_data) {
	WebClient* self = (WebClient*)nc->user_data;
	self->eventHandler(nc, ev, ev_data);
}


void WebClient::eventHandler(struct mg_connection *nc, int ev, void *ev_data){
	struct http_message *hm = (struct http_message *) ev_data;

	switch (ev) {
	case MG_EV_CONNECT:
		if (* (int *) ev_data != 0) {
			std::cerr << "connect() failed: "<< strerror(* (int *) ev_data) << std::endl;
			keepAlive = false;
		}
		break;
	case MG_EV_HTTP_REPLY:
		nc->flags |= MG_F_CLOSE_IMMEDIATELY;
#if WEB_CLIENT_LOG
		std::cout << "WC response with headers:" << std::endl;
		fwrite(hm->message.p, 1, hm->message.len, stdout);
		putchar('\n');
		//std::cout << "WC response without headers:" << std::endl;
		//fwrite(hm->body.p, 1, hm->body.len, stdout);
		putchar('\n');
#endif
		keepAlive = false;
		break;
	default:
		break;
	}
}


WebClient::WebClient(){
	mg_mgr_init(&mgr, NULL);
	s_show_headers = 0;
	keepAlive = true;
#if WEB_CLIENT_LOG
	std::cout << "WC constructor" << std::endl;
#endif
}


void WebClient::sendRegister(const std::string& postData){
#if WEB_CLIENT_LOG
	std::cout << "WC sendRegister" << std::endl;
#endif
	struct mg_connection *nc = mg_connect_http(
			&mgr,
			ev_handler,
			"http://shared-server.herokuapp.com/users",
			NULL,
			postData.c_str());
	nc->user_data = this;
	keepAlive = true;
	while (keepAlive) {
		mg_mgr_poll(&mgr, 1000);
	}
#if WEB_CLIENT_LOG
	std::cout << "WC sendRegister after while" << std::endl;
#endif
}


WebClient::~WebClient(){
	mg_mgr_free(&mgr);
}
