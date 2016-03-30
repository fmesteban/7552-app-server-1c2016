#include "WebServer.h"
#include <iostream>
#include <string>


void WebServer::handleURI(	struct mg_connection *networkConnection,
							const std::string& uri,
							mg_str *body){

	//pongo el valor en buf, correspondiente a la clave "number"
	//	mg_get_http_var(body, "number", buf, sizeof(buf));

	RequestHandler *hdlr = requestManager.getHanlder(uri);
	if( hdlr ){
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


void WebServer::eventHandler( struct mg_connection *nc, int ev, void *p ) {
	WebServer* self = (WebServer *) nc->user_data;
	struct http_message *httpMessage = (struct http_message *) p;

	if ( ev == MG_EV_HTTP_REQUEST ) {
		std::string temp(httpMessage->uri.p);
		std::string uri = temp.substr(0, httpMessage->uri.len);
		self->handleURI(nc, uri, &httpMessage->body);
	}
}


/**	WebServer constructor
 *	Wraps the mongoose server
 *	Protects the resources using the RAII pattern
 */
WebServer::WebServer() : httpPort( "8000" ){
	mg_mgr_init( &eventManager, NULL );
	networkConnection = mg_bind( &eventManager, httpPort.c_str(), eventHandler );
	networkConnection->user_data = this;

	s_http_server_opts.document_root = ".";
	s_http_server_opts.dav_document_root = ".";
	s_http_server_opts.enable_directory_listing = "yes";
	mg_set_protocol_http_websocket( networkConnection );

	std::cout << "Starting web server on port "<< httpPort << std::endl;
}


void WebServer::start(){
	while( true )
		mg_mgr_poll( &eventManager, 1000 );
}


WebServer::~WebServer() {
	mg_mgr_free( &eventManager );
}


