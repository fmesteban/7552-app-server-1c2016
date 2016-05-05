#include "Response.h"
#include <string>


Response::Response(){
	status = UNDEFINED_STATUS;
}


/*TODO: parse needed headers, etc...*/
void Response::parseMessage(struct http_message &httpMessage){
	body = std::string(httpMessage.body.p, httpMessage.body.len);
	std::cout << "body: " << body << std::endl;
	status = httpMessage.resp_code;
	std::cout << "resp_code: " << httpMessage.resp_code << std::endl;
}


std::string &Response::getBody(){
	return body;
}


httpStatus Response::getStatus(){
	return status;
}
