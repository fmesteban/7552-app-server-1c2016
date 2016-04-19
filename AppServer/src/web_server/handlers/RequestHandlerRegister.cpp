#include "RequestHandlerRegister.h"
#include <iostream>


RequestHandlerRegister::RequestHandlerRegister(Database& db) :
db(db),
RequestHandler("/register") {
}


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


void RequestHandlerRegister::run(struct mg_connection *networkConnection, mg_str *body){
	STRING_FROM_FIELD( userName );
	STRING_FROM_FIELD( userPassword );
	STRING_FROM_FIELD( userRealName );
	STRING_FROM_FIELD( userMail );
	STRING_FROM_FIELD( userBirthday );
	STRING_FROM_FIELD( userSex );

	db.putTwoLvlKeyValue(userName, "userName", userName);
	db.putTwoLvlKeyValue(userName, "password", userPassword); // TODO cambiar por password
	db.putTwoLvlKeyValue(userName, "realName", userRealName);
	db.putTwoLvlKeyValue(userName, "email", userMail);
	db.putTwoLvlKeyValue(userName, "birthday", userBirthday);
	db.putTwoLvlKeyValue(userName, "sex", userSex);

	std::string nombre;
	db.getTwoLvlValue(userName, "userName", nombre);

	sendHttpOk(networkConnection, "{ \"response\": \"hello " + nombre + "\" }\r\n");
}
