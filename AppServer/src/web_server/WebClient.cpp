#include <iostream>
#include <string>
#include <utility>
#include <map>
#include "WebClient.h"
#include "Request.h"
#include "Response.h"
#include <json/json.h>


/** Static function. Just calls the current instance's event handler.
 */
static void evHandler(struct mg_connection *networkConnection,
		int eventCode, void *eventData) {
	WebClient* self = (WebClient*)networkConnection->mgr->user_data;
	self->eventHandler(networkConnection, eventCode, eventData);
}


/** Handles an http response.
 */
void WebClient::eventHandler(struct mg_connection *networkConnection,
		int eventCode, void *eventData){
	struct http_message *httpMessage = (struct http_message *) eventData;
	int connect_status;

	if (eventCode == MG_EV_CONNECT){
		if (* (int *) eventData != 0) {
			std::cerr << "connect() failed: " <<
					strerror(* (int *) eventData) << std::endl;
			keepAlive = false;
		}
	} else if (eventCode == MG_EV_HTTP_REPLY){
		Response &resp = *(Response *) networkConnection->user_data;
		networkConnection->flags |= MG_F_CLOSE_IMMEDIATELY;
		resp.parseMessage(*httpMessage);
		keepAlive = false;
	}
}

/**	Inits the web client resources. (RAII)
 */
WebClient::WebClient() :
						remoteHost("shared-server.herokuapp.com:80"){
//						remoteHost("localhost:5000"){
	Log::instance()->append(
			"Initiating connection with " + remoteHost,
			Log::INFO);
	mg_mgr_init(&mgr, this);
	keepAlive = true;
}

/**	Sends a http post request to add a new user
 *  Returns a pair with the ID of the new user (-1 if error) and the
 *  status code of the shared server response.
 */
std::pair<int, int> WebClient::sendRegister(const std::string& postData){
	struct mg_connection *nc = NULL;
	int user_id;
	/* send the http request */
	if ((nc = mg_connect(&mgr, remoteHost.c_str(), evHandler)) != NULL) {
		mg_set_protocol_http_websocket(nc);
		Request requestToShared(*nc);
		Response responseFromShared;

		/* POST /users HTTP/1.1 */
		requestToShared.setMethod("POST");
		requestToShared.setUri("/users");

		/* setting headers */
		insertDefaultHeaders(requestToShared);

		/* sending the content */
		requestToShared.send(postData);
		Log::instance()->append(
				"Sending register request to shared server.",
				Log::INFO);

		/* start waiting for response */
		keepAlive = true;
		nc->user_data = &responseFromShared;
		while (keepAlive)
			mg_mgr_poll(&mgr, 1000);

		if(responseFromShared.getStatus() == 201){
			Log::instance()->append("Received OK from shared server.",
					Log::INFO);
			Json::Value root;
			Json::Reader reader;
			bool parsingSuccessful = reader.parse(
				responseFromShared.getBody(),
				root);
			Log::instance()->append("New user ID set to " +
				std::to_string(root.get("user", root).get("id", -1).asInt()),
				Log::INFO);
			return std::pair<int, int> (
					root.get("user", root).get("id", -1).asInt(), 201);
		}
		if(responseFromShared.getStatus() == 500){
			Log::instance()->append(
					"Received Internal Server Error from shared server.",
					Log::ERROR);
		}else{
			Log::instance()->append("Unknown error from shared server. Got " +
				std::to_string(responseFromShared.getStatus()),
				Log::ERROR);
		}
		return std::pair<int, int> (-1, responseFromShared.getStatus());
	}
	Log::instance()->append(
			"Unknown error while sending information to shared server.",
			Log::ERROR);
	return std::pair<int, int> (-1, -1);
}

/**	Sends a http put request to edit an existing user
 */
int WebClient::sendEditProfile(const std::string& putData,
		const std::string &userID){
	struct mg_connection *nc = NULL;

	/* send the http request */
	if ((nc = mg_connect(&mgr, remoteHost.c_str(), evHandler)) != NULL) {
		mg_set_protocol_http_websocket(nc);
		Request requestToShared(*nc);
		Response responseFromShared;

		/* PUT /users/<id> HTTP/1.1 */
		requestToShared.setMethod("PUT");
		requestToShared.setUri("/users/" + userID);

		/* setting headers */
		insertDefaultHeaders(requestToShared);

		/* sending the content */
		requestToShared.send(putData);
		Log::instance()->append(
				"Sending update profile request to shared server.",
				Log::INFO);

		/* start waiting for response */
		keepAlive = true;
		nc->user_data = &responseFromShared;
		while (keepAlive)
			mg_mgr_poll(&mgr, 1000);
		// TODO: capture possible error here.
		if(responseFromShared.getStatus() == 200){
			Log::instance()->append(
					"Received OK from shared server.",
					Log::INFO);
		}
		else if(responseFromShared.getStatus() == 500){
			Log::instance()->append(
					"Received internal server error from shared server.",
					Log::INFO);
		}else{
			Log::instance()->append(
					"Unknown error from shared server. Got " +
					std::to_string(responseFromShared.getStatus()),
					Log::ERROR);
		}
		return responseFromShared.getStatus();
	}
	return -1;
}

/** Sends a a http get request to get the information
 *  of an existing user.
 */
std::string WebClient::sendLogin(const std::string& userID){
	struct mg_connection *nc = NULL;

	/* send the http request */
	if ((nc = mg_connect(&mgr, remoteHost.c_str(), evHandler)) != NULL) {
		mg_set_protocol_http_websocket(nc);
		Request requestToShared(*nc);
		Response responseFromShared;

		/* POST /users HTTP/1.1 */
		requestToShared.setMethod("GET");
		requestToShared.setUri("/users/" + userID);

		/* setting headers */
		insertDefaultHeaders(requestToShared);

		/* sending the content */
		requestToShared.send("");
		Log::instance()->append(
				"Sending get user: " + userID +  " information request to shared server.",
				Log::INFO);

		/* start waiting for response */
		keepAlive = true;
		nc->user_data = &responseFromShared;

		while (keepAlive)
			mg_mgr_poll(&mgr, 1000);

		if (responseFromShared.getStatus() == 200){
			Log::instance()->append(
					"Received OK from shared server.",
					Log::INFO);
			return responseFromShared.getBody();
		}else if (responseFromShared.getStatus() == 404){
			Log::instance()->append(
					"Received not found error from shared server.",
					Log::INFO);
		}else if (responseFromShared.getStatus() == 500){
			Log::instance()->append(
					"Received internal server error from shared server.",
					Log::INFO);
		}else{
			Log::instance()->append(
					"Unknown error from shared server. Got " +
					std::to_string(responseFromShared.getStatus()),
					Log::ERROR);
		}
	}
	return "{}";
}

void WebClient::getUsers(std::map<int, User*> &usersById){
	struct mg_connection *nc = NULL;

	/* send the http request */
	if ((nc = mg_connect(&mgr, remoteHost.c_str(), evHandler)) != NULL) {
		mg_set_protocol_http_websocket(nc);
		Request requestToShared(*nc);
		Response responseFromShared;

		/* GET /users HTTP/1.1 */
		requestToShared.setMethod("GET");
		requestToShared.setUri("/users");

		/* setting headers */
		insertDefaultHeaders(requestToShared);

		/* sending the content */
		requestToShared.send("");
		Log::instance()->append(
				"Sending get users request to shared server.",
				Log::INFO);

		/* start waiting for response */
		keepAlive = true;
		nc->user_data = &responseFromShared;
		while (keepAlive)
			mg_mgr_poll(&mgr, 1000);

		/* check if response is on http error */
		if (responseFromShared.getStatus() == 404){
			Log::instance()->append(
					"Received not found error from shared server.",
					Log::INFO);
		}else if (responseFromShared.getStatus() == 500){
			Log::instance()->append(
					"Received internal server error from shared server.",
					Log::INFO);
		}else if (responseFromShared.getStatus() != 200){
			Log::instance()->append(
					"Unknown error from shared server. Got " +
					std::to_string(responseFromShared.getStatus()),
					Log::ERROR);
		}

		/* parse body to fill the users map */
		parseUsersMap(usersById, responseFromShared.getBody());
	}
}

/** Inserts a group of default headers to request.
 */
void WebClient::insertDefaultHeaders(Request &request){
	request.insertHeader("Host", remoteHost);
	request.insertHeader("Accept", "application/json, "
			"text/plain, */*; q=0.01");
	request.insertHeader("Accept-Language", "en-US,en;q=0.5");
	request.insertHeader("Accept-Encoding", "gzip, deflate");
	request.insertHeader("Connection", "keep-alive");
	request.insertHeader("Content-Type", "application/json");
}

void WebClient::parseUsersMap(
		std::map<int, User*> &usersById,
		const std::string &body){
	/* Loads the response into a JSON Value object */
	Json::Value root;
	Json::Reader reader;
	bool parsingSuccessful = reader.parse(body, root);
	if (!parsingSuccessful){
		Log::instance()->append(
				"Received an malformed response from shared after send a GET users.",
				Log::INFO);
		return;
	}

	Json::Value &usersList = root["users"];
	Json::ValueConstIterator iterUsers = usersList.begin();

	for (; iterUsers != usersList.end(); ++iterUsers){
		const Json::Value& user = (*iterUsers)["user"];
		int id(user["id"].asInt());
		std::string name(user["name"].asString());
		std::string alias(user["alias"].asString());
		std::string email(user["email"].asString());
		std::string photoUrl(user["photo_profile"].asString());
		std::string sex(user["sex"].asString());
		float longitude(user["location"]["longitude"].asFloat());
		float latitude(user["location"]["latitude"].asFloat());
		int age(user["age"].asInt());

		User *newUser = new User(
				name, alias, "undef_password",
				email, age, sex,
				longitude, latitude, photoUrl);

		newUser->setId(id);

		const Json::Value &interestsList = user["interests"];
		Json::ValueConstIterator iterInterests = interestsList.begin();
		for(; iterInterests != interestsList.end(); ++iterInterests){
			newUser->addInterest(
					(*iterInterests)["category"].asString(),
					(*iterInterests)["value"].asString());
		}
		usersById.insert(std::pair<int,User*>(id, newUser));
	}
}

WebClient::~WebClient(){
	mg_mgr_free(&mgr);
}
