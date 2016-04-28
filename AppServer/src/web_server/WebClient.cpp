#include "WebClient.h"
#include <iostream>
#include <string>


/** Static function. Just calls the current instance's event handler.
 */
static void evHandler(struct mg_connection *networkConnection,
		int eventCode, void *eventData) {
	WebClient* self = (WebClient*)networkConnection->mgr->user_data;
	self->eventHandler(networkConnection, eventCode, eventData);
}


/** Handles an http response.
 */
void WebClient::eventHandler(struct mg_connection *networkConnection,
		int eventCode, void *eventData){
	struct http_message *hm = (struct http_message *) eventData;
	int connect_status;

	switch (eventCode) {
	case MG_EV_CONNECT:
		if (* (int *) eventData != 0) {
			std::cerr << "connect() failed: " <<
					strerror(* (int *) eventData) << std::endl;
			keepAlive = false;
		}
		break;
	case MG_EV_HTTP_REPLY:
		networkConnection->flags |= MG_F_CLOSE_IMMEDIATELY;
		std::cout << "WC response with headers:" << std::endl;
		fwrite(hm->message.p, 1, hm->message.len, stdout);
		putchar('\n');
		keepAlive = false;
		break;
	default:
		break;
	}
}

/**	Inits the web client resources. (RAII)
 */
WebClient::WebClient() :
		remoteHost("shared-server.herokuapp.com:80"){
	mg_mgr_init(&mgr, this);
	keepAlive = true;
}

/**	Sends a http post request to add a new user
 * TODO: a class Request, and another Response, che!
 */
void WebClient::sendRegister(const std::string& postData){
	struct mg_connection *nc = NULL;

	/* send the http request */
	if ((nc = mg_connect(&mgr, remoteHost.c_str(), evHandler)) != NULL) {
		mg_set_protocol_http_websocket(nc);
		mg_printf(nc,
				"POST /users HTTP/1.1\r\n"
				"Host: %s\r\n"
				"Accept: application/json, text/plain, "
				"*/*; q=0.01\r\n"
				"Accept-Language: en-US,en;q=0.5\r\n"
				"Accept-Encoding: gzip, deflate\r\n"
				"Connection: keep-alive\r\n"
				"Content-Type: text/plain\r\n"
				"Content-Length: %" SIZE_T_FMT "\r\n"
				"\r\n%s\r\n",
				remoteHost.c_str(),
				postData.size(), postData.c_str());
	}

	/* start waiting for response */
	keepAlive = !!nc;
	while (keepAlive)
		mg_mgr_poll(&mgr, 1000);
}

/** Sends a a http get request to get the information
 * of an existing user.
 * TODO: a class Request, and another Response, che!
 */
void WebClient::sendLogin(const std::string& postData){
	// TODO: implement
}

WebClient::~WebClient(){
	mg_mgr_free(&mgr);
}
