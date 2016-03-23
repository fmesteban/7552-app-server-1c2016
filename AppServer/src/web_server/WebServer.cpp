#include "WebServer.h"
#include <iostream>
#include <string>


int WebServer::is_websocket(const struct mg_connection *nc) {
	return nc->flags & MG_F_IS_WEBSOCKET;
}

void WebServer::broadcast(struct mg_connection *nc, const char *msg, size_t len) {
	struct mg_connection *c;
	char buf[500];

	snprintf(buf, sizeof(buf), "%p %.*s", nc, (int) len, msg);
	for (c = mg_next(nc->mgr, NULL); c != NULL; c = mg_next(nc->mgr, c)) {
		mg_send_websocket_frame(c, WEBSOCKET_OP_TEXT, buf, strlen(buf));
	}
}

static void eventHandler( struct mg_connection *nc, int ev, void *p ) {
	WebServer* self = (WebServer *) nc->user_data;
	struct http_message *httpMessage = (struct http_message *) p;
	struct websocket_message *websocketMessage = (struct websocket_message *) p;

	switch (ev) {
	case MG_EV_HTTP_REQUEST:
	{
		std::string s1(httpMessage->uri.p);
		std::string s = s1.substr(0, httpMessage->uri.len);
		std::cout << "http" << s << std::endl;
		if(mg_vcmp(&httpMessage->uri, "/api/post/number") == 0){
			char buf[100];
			/* Get form variables */
			mg_get_http_var(&httpMessage->body, "number", buf, sizeof(buf));
			std::cout << "receiving: " << buf << std::endl;
			mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
			mg_printf_http_chunk(nc, "{ \"response\": %lf }", strtod(buf, NULL)*strtod(buf, NULL));
			mg_send_http_chunk(nc, "", 0);
			break;
		}
		/* Usual HTTP request - serve static files */
		mg_serve_http(nc, httpMessage, self->s_http_server_opts);
		nc->flags |= MG_F_SEND_AND_CLOSE;
		break;
	}
	case MG_EV_WEBSOCKET_HANDSHAKE_DONE:
		/* New websocket connection. Tell everybody. */
		self->broadcast(nc, "joined", 6);
		break;
	case MG_EV_WEBSOCKET_FRAME:
		/* New websocket message. Tell everybody. */
		self->broadcast(nc, (char *) websocketMessage->data, websocketMessage->size);
		break;
	case MG_EV_CLOSE:
		/* Disconnect. Tell everybody. */
		if (self->is_websocket(nc)) {
			self->broadcast(nc, "left", 4);
		}
		break;
	default:
		break;
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


