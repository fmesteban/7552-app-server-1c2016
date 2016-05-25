#include "RequestHandlerRegister.h"
#include "Response.h"
#include "User.h"
#include <iostream>
#include <string>


RequestHandlerRegister::RequestHandlerRegister(UsersContainer &users) :
users(users),
RequestHandler("/register") {
}

/** Parse the /register uri input, and saves it in the app-server
 * 	database.
 *
 */
void RequestHandlerRegister::run(Request &request){
	Log::instance()->append("Received a register request", Log::INFO);
	if (request.getMethod() != "POST"){
		RequestHandler::sendHttpOk(
			request.getNetworkConnection(),
			"{ \"response\": \"POST\" }\r\n");
		Log::instance()->append("Not a POST request. Rejected.", Log::INFO);
		return;
	}
	Json::Value root;
	Json::Reader reader;
	bool parsingSuccessful = reader.parse(request.getBody(), root);
	if (!parsingSuccessful){
		Response response(BAD_REQUEST_STATUS, BAD_REQUEST_MSG);
		RequestHandler::sendResponse(response, request.getNetworkConnection());
		Log::instance()->append("Received a BAD (malformed) REQUEST. Rejected.", Log::INFO);
		return;
	}

	std::string name = root.get("name", "unavailable").asString();
	std::string alias = root.get("alias", "unavailable").asString();
	std::string password = root.get("password", "unavailable").asString();
	std::string email = root.get("email", "unavailable").asString();
	std::string birthday = root.get("birthday", "unavailable").asString();
	std::string sex = root.get("sex", "unavailable").asString();
	std::string photoProfile = root.get("photo_profile", "unavailable").asString();

	Json::Value location;
	reader.parse(root.get("location", "unavailable").asString(), location);
	
	std::string longitudeStr = location.get("longitude", "unavailable").asString();
	std::string latitudeStr = location.get("latitude", "unavailable").asString();
	
	if(name == "unavailable" || 
		alias == "unavailable" || 
		password == "unavailable" || 
		email == "unavailable" || 
		birthday == "unavailable" || 
		sex == "unavailable" || 
		photoProfile == "unavailable" || 
		longitudeStr == "unavailable" || 
		latitudeStr == "unavailable"){
			Response response(BAD_REQUEST_STATUS, BAD_REQUEST_MSG);
			RequestHandler::sendResponse(response, request.getNetworkConnection());
			Log::instance()->append("Received a BAD (incomplete) REQUEST. Rejected.", Log::INFO);
			return;
	}

	std::cout << "name: " << name << std::endl;
	std::cout << "alias: " << alias << std::endl;
	std::cout << "password: " << password << std::endl;
	std::cout << "email: " << email << std::endl;
	std::cout << "birthday: " << birthday << std::endl;
	std::cout << "sex: " << sex << std::endl;
	std::cout << "photoProfile: " << photoProfile << std::endl;
	std::cout << "longitude: " << longitudeStr << std::endl;
	std::cout << "latitude: " << latitudeStr << std::endl;

	std::stringstream aux;
	float longitude, latitude;
	aux << longitudeStr;
	aux >> longitude;
	aux.clear();
	aux << latitudeStr;
	aux >> latitude;

	User newUser(name, alias, password, email, birthday, sex, 
					longitude, latitude, photoProfile);
	newUser.addInterest("Music", "Foo Fighters");

	users.add(newUser);

	Response response(ACCEPTED_STATUS, ACCEPTED_MSG);
	RequestHandler::sendResponse(response, request.getNetworkConnection());
	Log::instance()->append("Received an OK REQUEST. Accepted.", Log::INFO);
}
