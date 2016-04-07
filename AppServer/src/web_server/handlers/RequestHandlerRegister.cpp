#include "RequestHandlerRegister.h"


RequestHandlerRegister::RequestHandlerRegister() :
RequestHandler("/register"){
}


void RequestHandlerRegister::run(struct mg_connection *networkConnection, mg_str *body){
	mg_printf(networkConnection,
			"HTTP/1.1 201 OK\r\n"
			"Access-Control-Allow-Origin: *\r\n"
			"Transfer-Encoding: chunked\r\n"
			"\r\n");

	mg_printf_http_chunk(networkConnection, "{ \"response\": 210 }\r\n");
	mg_send_http_chunk(networkConnection, "", 0);
}
