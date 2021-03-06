/** Include area. */
#include "WebServer.h"
#include <iostream>
#include <string>


/** Executes the corresponding header for client's request.
 *
 *	\param request Is the user's request.
 */
void WebServer::handleRequest(Request &request){
	RequestHandler &hdlr = requestManager.getHanlder(request.getUri());
	hdlr.run(request);
}


/** Static function: just call the current instance's uri handler function
 *
 *	\param networkConnection Mongoose network connection struct.
 *	\param eventCode Mongoose event code.
 *	\param dataPointer Mongoose event data, could be the http message.
 *
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
 *	Protects the resources using the RAII pattern.
 *
 *	\param port Is the port of listener socket, as string.
 */
WebServer::WebServer(const std::string &port) : httpPort(port),
		suggestionsGenerator(users),
		requestManager(users, suggestionsGenerator) {
	keepAlive = true;
	mg_mgr_init(&eventManager, NULL);
	networkConnection = mg_bind(&eventManager, httpPort.c_str(), eventHandler);
	networkConnection->user_data = this;

	serverOptions.document_root = ".";
	serverOptions.dav_document_root = ".";
	serverOptions.enable_directory_listing = "yes";
	mg_set_protocol_http_websocket(networkConnection);
	Log::instance()->append("Starting web server on port " + httpPort, Log::INFO);
}


/**	Starts the Server Polling loop.
 *
 */
void WebServer::run(){
	while(keepAlive)
		mg_mgr_poll(&eventManager, 1000);
}


/** Stops the Server Polling loop.
 *
 */
void WebServer::stop(){
	keepAlive = false;
	Log::instance()->append("Shutting down server.", Log::INFO);
}


/** Releases the WebServer.
 *
 */
WebServer::~WebServer(){
	mg_mgr_free(&eventManager);
}
