#include "WebClient.h"
#include <iostream>
#include <string>
#include "Request.h"
#include "Response.h"
#include <json/json.h>


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
	struct http_message *httpMessage = (struct http_message *) eventData;
	int connect_status;

	if (eventCode == MG_EV_CONNECT){
		if (* (int *) eventData != 0) {
			std::cerr << "connect() failed: " <<
					strerror(* (int *) eventData) << std::endl;
			keepAlive = false;
		}
	} else if (eventCode == MG_EV_HTTP_REPLY){
		Response &resp = *(Response *) networkConnection->user_data;
		networkConnection->flags |= MG_F_CLOSE_IMMEDIATELY;
		resp.parseMessage(*httpMessage);
		keepAlive = false;
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
 */
int WebClient::sendRegister(const std::string& postData){
	struct mg_connection *nc = NULL;

	/* send the http request */
	if ((nc = mg_connect(&mgr, remoteHost.c_str(), evHandler)) != NULL) {
		mg_set_protocol_http_websocket(nc);
		Request requestToShared(*nc);
		Response responseFromShared;

		/* POST /users HTTP/1.1 */
		requestToShared.setMethod("POST");
		requestToShared.setUri("/users");

		/* setting headers */
		requestToShared.insertHeader("Host", remoteHost);
		requestToShared.insertHeader("Accept", "application/json, "
				"text/plain, */*; q=0.01");
		requestToShared.insertHeader("Accept-Language", "en-US,en;q=0.5");
		requestToShared.insertHeader("Accept-Encoding", "gzip, deflate");
		requestToShared.insertHeader("Connection", "keep-alive");
		requestToShared.insertHeader("Content-Type", "text/plain");

		/* sending the content */
		requestToShared.send(postData);

		/* start waiting for response */
		keepAlive = true;
		nc->user_data = &responseFromShared;
		while (keepAlive)
			mg_mgr_poll(&mgr, 1000);

		if(responseFromShared.getStatus() == 201){
			Json::Value root;
			Json::Reader reader;
			bool parsingSuccessful = reader.parse(responseFromShared.getBody(), root);
			return root.get("id", -1).asInt();
		}
	}

	return -1;
}


/** Sends a a http get request to get the information
 * of an existing user.
 */
void WebClient::sendLogin(const std::string& postData){
	// TODO: implement
}


WebClient::~WebClient(){
	mg_mgr_free(&mgr);
}
