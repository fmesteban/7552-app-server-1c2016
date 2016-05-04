#ifndef WEB_SERVER_REQUEST_H_
#define WEB_SERVER_REQUEST_H_

#include <map>
#include <string>
#include "mongoose.h"

class Request {
private:
	std::string method;
	std::string uri;
	std::map<std::string, std::string> headers;
	std::string body;
	struct mg_connection &networkConnection;

public:
	Request(struct mg_connection &networkConnection,
			struct http_message &httpMessage);
	explicit Request(struct mg_connection &networkConnection);
	void setMethod(const std::string &method);
	void setUri(const std::string &uri);
	void insertHeader(const std::string &name, const std::string &value);
	std::string &getUri();
	std::string &getBody();
	void send(const std::string &content);

	struct mg_connection *getNetworkConnection(){
		return &networkConnection;
	}
};

#endif
