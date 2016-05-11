#ifndef WEB_SERVER_INTEREST_H_
#define WEB_SERVER_INTEREST_H_

#include <string>
#include <ostream>

class Interest {
private:
	std::string category;
	std::string value;

public:
	Interest(const std::string &category, const std::string &value);
	friend std::ostream & operator<<(std::ostream &os, const Interest& self);
};

#endif
