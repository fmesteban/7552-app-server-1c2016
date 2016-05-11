#include "RequestHandlerRegister.h"
#include <iostream>
#include <string>
#include "Response.h"
#include "User.h"


RequestHandlerRegister::RequestHandlerRegister(UsersContainer &users) :
users(users),
RequestHandler("/register") {
}


/** Parse the /register uri input, and saves it in the app-server
 * 	database.
 *
 */
void RequestHandlerRegister::run(Request &request){
	if (request.getMethod() != "POST"){
		RequestHandler::sendHttpOk(
			request.getNetworkConnection(),
			"{ \"response\": \"POST\" }\r\n");
		return;
	}
	Json::Value root;
	Json::Reader reader;
	bool parsingSuccessful = reader.parse(request.getBody(), root);
	if (!parsingSuccessful){
		/* malformed json data */
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
	
	std::string longitudeStr = location.get("longitude", "0.5").asString();
	std::string latitudeStr = location.get("latitude", "0.5").asString();
	std::cout << "latitudeStr: " << latitudeStr << std::endl;

	std::stringstream aux;
	float longitude, latitude;
	aux << longitudeStr;
	aux >> longitude;
	aux.clear();
	aux << latitudeStr;
	aux >> latitude;

	std::cout << "name: " << name << std::endl;
	std::cout << "alias: " << alias << std::endl;
	std::cout << "password: " << password << std::endl;
	std::cout << "email: " << email << std::endl;
	std::cout << "birthday: " << birthday << std::endl;
	std::cout << "sex: " << sex << std::endl;
	std::cout << "photoProfile: " << photoProfile << std::endl;
	std::cout << "longitude: " << longitude << std::endl;
	std::cout << "latitude: " << latitude << std::endl;

	User newUser(name, alias, password, email, birthday, sex, 
					longitude, latitude, photoProfile);
	newUser.addInterest("music", "Foo Fighters");

	users.add(newUser);

	RequestHandler::sendHttpOk(
		request.getNetworkConnection(),
		"{ \"response\": \"OK\" }\r\n");
}
