#include "WebServer.h"
#include <iostream>
#include <string>


void WebServer::handleRequest(Request &request){
	RequestHandler &hdlr = requestManager.getHanlder(request.getUri());
	hdlr.run(request);
}


/** Static function: just call the current instance's uri handler function
 */
void WebServer::eventHandler(struct mg_connection *networkConnection,
		int eventCode, void *dataPointer){
	if (eventCode == MG_EV_HTTP_REQUEST){
		WebServer* self = (WebServer *) networkConnection->user_data;
		struct http_message *httpMessage = (struct http_message *) dataPointer;

		Request request(*networkConnection, *httpMessage);
		self->handleRequest(request);
	}
}


/**	WebServer constructor
 *	Wraps the mongoose server
 *	Protects the resources using the RAII pattern
 */
WebServer::WebServer(const std::string &port) : httpPort(port),
		requestManager(users){
	keepAlive = true;
	mg_mgr_init(&eventManager, NULL);
	networkConnection = mg_bind(&eventManager, httpPort.c_str(), eventHandler);
	networkConnection->user_data = this;

	serverOptions.document_root = ".";
	serverOptions.dav_document_root = ".";
	serverOptions.enable_directory_listing = "yes";
	mg_set_protocol_http_websocket(networkConnection);

	std::cout << "Starting web server on port "<< httpPort << std::endl;
}


/**	Starts the Server Polling loop.
 */
void WebServer::run(){
	while(keepAlive)
		mg_mgr_poll(&eventManager, 1000);
}

void WebServer::stop(){
	keepAlive = false;
}


/** Releases the WebServer.
 */
WebServer::~WebServer(){
	mg_mgr_free(&eventManager);
}

