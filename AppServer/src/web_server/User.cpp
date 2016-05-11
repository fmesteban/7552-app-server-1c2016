#include "User.h"
#include "Interest.h"
#include <string>
#include <sstream>
#include <vector>


User::User(const std::string &name,
		const std::string &alias,
		const std::string &password,
		const std::string &email,
		const std::string &birthday,
		const std::string &sex, float longitude, float latitude,
		const std::string &photoProfile) :
	name(name),
	alias(alias),
	password(password),
	email(email),
	birthday(birthday),
	sex(sex),
	longitude(longitude),
	latitude(latitude),
	photoProfile(photoProfile){
}

void User::addInterest(const std::string& category, const std::string &value){
	interests.push_back(new Interest(category, value));
}


std::ostream& operator<<(std::ostream &os, const User& self) {
	os << "{\"user\":{";
	self.printInterests(os);
	os <<
			"\"name\": \"" 	<< self.name 		<< "\","
			"\"alias\": \"" << self.alias 	<< "\","
			"\"email\": \"" << self.email 		<< "\","
			"\"sex\": \"" 	<< self.sex 		<< "\","
			"\"photo_profile\": \"" << self.photoProfile << "\","
			"\"location\":"
			"{"
				"\"latitud\": " << self.latitude << ","
				"\"longitud\": " << self.longitude <<
			"}"
		"}"
	"}";

	return os;
}


/* Builds the interests json list */
void User::printInterests(std::ostream &os) const{
	os << 
	"\"interests\":[";
	if (interests.empty()){
		/* the json output list should not be empty */
		os << "{\"category\":\"music\",\"value\":\"none\"}";
	}else{
		for (size_t i=0; i < interests.size() - 1; ++i){
			/* with comma */
			os << *interests[i] << ",";
		}
		/* without comma */
		os << *interests[interests.size() - 1];
	}
	os << "],";
}


User::~User(){
	std::vector<Interest*>::iterator interest = interests.begin();
	for(; interest != interests.end(); ++interest)
		delete *interest;
}
