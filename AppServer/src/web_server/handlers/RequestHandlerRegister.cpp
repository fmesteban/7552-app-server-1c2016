#include "RequestHandlerRegister.h"
#include <iostream>
#include <string>


RequestHandlerRegister::RequestHandlerRegister(UsersContainer &users) :
users(users),
RequestHandler("/register") {
}


/** Sends an 201 OK response to \nc, appending the \extraLine
 *
 */
void RequestHandlerRegister::sendHttpOk(struct mg_connection *nc,
		const std::string &extraLine){
	mg_printf(nc,
			"HTTP/1.1 201 OK\r\n"
			"Access-Control-Allow-Origin: *\r\n"
			"Transfer-Encoding: chunked\r\n"
			"\r\n");

	mg_printf_http_chunk(nc, extraLine.c_str());
	mg_send_http_chunk(nc, "", 0);
}


/** Parse the register uri input, and saves it in the app-server
 * 	database. TODO: send the data to the shared-server
 *
 */
void RequestHandlerRegister::run(
		struct mg_connection *networkConnection,
		mg_str *body){
	INIT_JSON;
	STRING_FROM_FIELD(userName);
	STRING_FROM_FIELD(userPassword);
	STRING_FROM_FIELD(userRealName);
	STRING_FROM_FIELD(userMail);
	STRING_FROM_FIELD(userBirthday);
	STRING_FROM_FIELD(userSex);

	users.add(
			userName,
			userPassword,
			userRealName,
			userMail,
			userBirthday,
			userSex);

	sendHttpOk(
			networkConnection,
			"{ \"response\": \"hello " + userName + "\" }\r\n");
}
