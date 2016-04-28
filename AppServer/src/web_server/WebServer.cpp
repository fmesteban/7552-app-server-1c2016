#include "WebServer.h"
#include <iostream>
#include <string>


/** Receives an http URI, gets the corresponding RequestHandler, and
 * 	executes it.
 * 	TODO: por ahora, cuando no hay handler devuelve un 200 OK hard,
 * 		devolver NotFound
 *
 */
void WebServer::handleURI(struct mg_connection *networkConnection,
							const std::string& uri,
							mg_str *body){
	std::cout << "uri: " << uri << std::endl;

	RequestHandler *hdlr = requestManager.getHanlder(uri);
	if(hdlr){
		hdlr->run(networkConnection, body);
	}else{
		//si es null, por ahora devuelvo esto
		mg_printf(networkConnection,
				"HTTP/1.1 200 OK\r\n"
				"Access-Control-Allow-Origin: *\r\n"
				"Transfer-Encoding: chunked\r\n"
				"\r\n");
		mg_printf_http_chunk(networkConnection, "{ \"response\": 200 }\r\n");
		mg_send_http_chunk(networkConnection, "", 0);
	}
}


/** Static function: just call the current instance's uri handler function
 */
void WebServer::eventHandler(struct mg_connection *networkConnection,
		int eventCode, void *dataPointer){
	WebServer* self = (WebServer *) networkConnection->user_data;
	struct http_message *httpMessage = (struct http_message *) dataPointer;

	if (eventCode == MG_EV_HTTP_REQUEST){
		std::string temp(httpMessage->uri.p);
		std::string uri = temp.substr(0, httpMessage->uri.len);
		std::cout << "an HTTP event with uri: " << uri << std::endl;
		self->handleURI(networkConnection, uri, &httpMessage->body);
	}
}


/**	WebServer constructor
 *	Wraps the mongoose server
 *	Protects the resources using the RAII pattern
 */
WebServer::WebServer() : httpPort("8000"),
		requestManager(users){
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
void WebServer::start(){
	while(true)
		mg_mgr_poll(&eventManager, 1000);
}


/** Releases the WebServer.
 */
WebServer::~WebServer(){
	mg_mgr_free(&eventManager);
}

