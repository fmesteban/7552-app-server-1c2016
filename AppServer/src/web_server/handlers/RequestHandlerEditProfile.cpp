/** Include area. */
#include "RequestHandlerEditProfile.h"
#include "Response.h"
#include "User.h"
#include <iostream>
#include <string>


/*------------------------------------------------------------------------
 * 	Member Functions Implementations
 * ---------------------------------------------------------------------*/

/** Request handler edit profile will handle the uri "/updateprofile".
 *
 * 	\param users Is the server users container.
 */
RequestHandlerEditProfile::RequestHandlerEditProfile(UsersContainer &users) :
users(users),
RequestHandler("/updateprofile") {
}


/** Parse the /register uri input, and saves it in the app-server
 * 	database.
 *
 *	\param request Is the request sent by client.
 */
void RequestHandlerEditProfile::run(Request &request){
	Log::instance()->append("Received a profile update request", Log::INFO);

	if (request.getMethod() != "POST"){
		/* some libraries send OPTIONS before POST */
		Response response(BAD_REQUEST_STATUS, BAD_REQUEST_MSG);
		RequestHandler::sendResponse(response, request.getNetworkConnection());
		Log::instance()->append("Not a POST request. Rejected.", Log::INFO);
		return;
	}
	/* Loads the request into a JSON Value object */
	Json::Value root;
	Json::Reader reader;
	bool parsingSuccessful = reader.parse(request.getBody(), root);
	if (!parsingSuccessful){
		Response response(BAD_REQUEST_STATUS, BAD_REQUEST_MSG);
		RequestHandler::sendResponse(response, request.getNetworkConnection());
		Log::instance()->append(
				"Received a BAD (malformed) REQUEST. Rejected.",
				Log::INFO);
		return;
	}

	std::string name = root.get("name", "unavailable").asString();
	std::string alias = root.get("alias", "unavailable").asString();
	std::string email = root.get("email", "unavailable").asString();
	std::string age_str = root.get("age", "unavailable").asString();
	int age;
	std::stringstream(age_str) >> age ? age : 0;
	std::string sex = root.get("sex", "unavailable").asString();
	std::string photoProfile = root.get("photo_profile", "unavailable").asString();

	Json::Value &location = root["location"];
	
	std::string longitudeStr = location.get("longitude", "unavailable").asString();
	std::string latitudeStr = location.get("latitude", "unavailable").asString();
	
	if(name == "unavailable" || 
		alias == "unavailable" || 
		email == "unavailable" || 
		sex == "unavailable" || 
		photoProfile == "unavailable" || 
		longitudeStr == "unavailable" || 
		latitudeStr == "unavailable"){
			Response response(BAD_REQUEST_STATUS, BAD_REQUEST_MSG);
			RequestHandler::sendResponse(response,
					request.getNetworkConnection());
			Log::instance()->append(
					"Received a BAD (incomplete) REQUEST. Rejected.",
					Log::INFO);
			return;
	}
	std::stringstream aux;
	float longitude, latitude;
	aux << longitudeStr;
	aux >> longitude;
	aux.clear();
	aux << latitudeStr;
	aux >> latitude;

	User newProfile(name, alias, "unchanged_password", email, age, sex,
					longitude, latitude, photoProfile);

	/* Parse interests array */
	Json::Value& interests = root["interests"];
	Json::ValueConstIterator it = interests.begin();
	for (; it != interests.end(); ++it)
	{
		const Json::Value& interest = *it;
		std::string category = interest.get(
				"category", "unavailable").asString();
		std::string value = interest.get("value", "unavailable").asString();
		if(category == "unavailable" || value == "unavailable")
			continue;
		newProfile.addInterest(category, value);
	}
	/* Edits the pre-existent user in users container */
	int response_status = users.edit(newProfile);
	if (response_status == -1){
		Log::instance()->append(
				"Unknown ERROR on APP SERVER.",
				Log::ERROR);
		response_status = 500;
	}

	/* Sends response to the client */
	Response response(response_status, ACCEPTED_MSG);
	RequestHandler::sendResponse(response, request.getNetworkConnection());
}
