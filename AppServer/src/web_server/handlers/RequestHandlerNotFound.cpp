#include "RequestHandlerNotFound.h"
#include <string>


RequestHandlerNotFound::RequestHandlerNotFound() :
RequestHandler(""){
}


void RequestHandlerNotFound::run(
		struct mg_connection *networkConnection,
		mg_str *body){
//	mg_printf(networkConnection,
//			"HTTP/1.1 404 Error Not Found\r\n"
//			"Access-Control-Allow-Origin: *\r\n"
//			"Transfer-Encoding: chunked\r\n"
//			"\r\n");
//
	mg_printf(networkConnection,
			"HTTP/1.1 201 OK\r\n"
			"Access-Control-Allow-Origin: *\r\n"
			"Transfer-Encoding: chunked\r\n"
			"\r\n");
	mg_printf_http_chunk(networkConnection, "{ \"response\": \"Not Found\" }\r\n");
	mg_send_http_chunk(networkConnection, "", 0);
}
