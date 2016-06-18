#ifndef WEB_SERVER_USER_H_
#define WEB_SERVER_USER_H_

#include "Interest.h"
#include "Database.h"
#include <string>
#include <vector>
#include <map>


/* forward declaration */
class Suggestion;

class User {
private:
	std::string name;
	std::string alias;
	std::string password;
	std::string email;
	std::string sex;
	int age;
	float longitude;
	float latitude;
	std::string photoProfile;
	std::vector<Interest*> interests;
	int id;
	void printInterests(std::ostream &os) const;
	std::map<int, Suggestion*> sugestions;

public:
	User(const std::string &name,
			const std::string &alias,
			const std::string &password,
			const std::string &email,
			int age,
			const std::string &sex,
			float longitude, float latitude,
			const std::string &photoProfile);
	User(Database &db, const std::string &email);
	void addInterest(const std::string& category, const std::string &value);
	void setId(int id);
	int getID();
	void setId(const std::string& id);
	void saveIn(Database &db);
	const std::string &getEmail() const;
	friend std::ostream & operator<<(std::ostream &os, const User& self);
	void addSuggestion(Suggestion* newSuggestion);
	void edit(User& newProfile);
	std::string getSomeInterestFromCategory(std::string &category);
	bool couldMatch(User &another);
	~User();
};

#endif
