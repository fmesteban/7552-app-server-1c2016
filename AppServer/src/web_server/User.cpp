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
	id = -1;
}


User::User(Database &db, const std::string &email){
}


/* db registers: (email, id) */
void User::saveIn(Database &db){
	std::stringstream ss;
	ss << id;
	db.putKeyValue(email, ss.str());
	Log::instance()->append("User with email " + email + "saved in DB.", Log::INFO);
}


void User::addInterest(const std::string& category, const std::string &value){
	interests.push_back(new Interest(category, value));
}


void User::setId(int id){
	this->id = id;
}

void User::setId(const std::string& id){
	std::stringstream ss;
	ss << id;
	int idAsInt;
	ss >> idAsInt;
	setId(idAsInt);
}


std::ostream& operator<<(std::ostream &os, const User& self) {
	os << "{\"user\":{";
	self.printInterests(os);
	if(self.id != -1)
		os << "\"id\": " 	<< self.id			<< ",";

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

const std::string &User::getEmail() const{
	return email;
}


User::~User(){
	std::vector<Interest*>::iterator interest = interests.begin();
	for(; interest != interests.end(); ++interest)
		delete *interest;
}
