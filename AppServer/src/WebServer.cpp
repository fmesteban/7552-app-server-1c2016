#include "WebServer.h"
#include <iostream>

struct mg_serve_http_opts s_http_server_opts;


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

void WebServer::eventHandler(struct mg_connection *nc, int ev, void *p) {
	  struct http_message *hm = (struct http_message *) p;
	  struct websocket_message *wm = (struct websocket_message *) p;

	  switch (ev) {
	    case MG_EV_HTTP_REQUEST:
	      /* Usual HTTP request - serve static files */
	      mg_serve_http(nc, hm, s_http_server_opts);
	      nc->flags |= MG_F_SEND_AND_CLOSE;
	      break;
	    case MG_EV_WEBSOCKET_HANDSHAKE_DONE:
	      /* New websocket connection. Tell everybody. */
	      broadcast(nc, "joined", 6);
	      break;
	    case MG_EV_WEBSOCKET_FRAME:
	      /* New websocket message. Tell everybody. */
	      broadcast(nc, (char *) wm->data, wm->size);
	      break;
	    case MG_EV_CLOSE:
	      /* Disconnect. Tell everybody. */
	      if (is_websocket(nc)) {
	        broadcast(nc, "left", 4);
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


