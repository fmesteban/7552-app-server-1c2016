#ifndef WEB_SERVER_USER_H_
#define WEB_SERVER_USER_H_

#include "Interest.h"
#include <string>
#include <vector>

class User {
private:
	std::string name;
	std::string alias;
	std::string password;
	std::string email;
	std::string birthday;
	std::string sex;
	float longitude;
	float latitude;
	std::string photoProfile;
	std::vector<Interest*> interests;
	void printInterests(std::ostream &os) const;

public:
	User(const std::string &name,
			const std::string &alias,
			const std::string &password,
			const std::string &email,
			const std::string &birthday,
			const std::string &sex,
			float longitude, float latitude,
			const std::string &photoProfile);
	void addInterest(const std::string& category, const std::string &value);
	friend std::ostream & operator<<(std::ostream &os, const User& self);
	~User();
};

#endif
