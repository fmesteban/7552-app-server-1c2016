#include "RequestHandlerEditProfile.h"
#include "Response.h"
#include "User.h"
#include <iostream>
#include <string>


RequestHandlerEditProfile::RequestHandlerEditProfile(UsersContainer &users) :
users(users),
RequestHandler("/updateprofile") {
}


/** Parse the /register uri input, and saves it in the app-server
 * 	database.
 *
 */
void RequestHandlerEditProfile::run(Request &request){
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
		/* Bad Request */
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
		/* Bad Request */
	}

	std::stringstream aux;
	float longitude, latitude;
	aux << longitudeStr;
	aux >> longitude;
	aux.clear();
	aux << latitudeStr;
	aux >> latitude;

	User newProfile(name, alias, password, email, birthday, sex, 
					longitude, latitude, photoProfile);
	newProfile.addInterest("Music", "Pink Floyd");

	users.edit(newProfile);

	RequestHandler::sendHttpOk(
		request.getNetworkConnection(),
		"{ \"response\": \"OK\" }\r\n");
}
