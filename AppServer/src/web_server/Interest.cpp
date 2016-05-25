#include "Interest.h"
#include <string>
#include <ostream>

Interest::Interest(const std::string &category, const std::string &value) :
	category(category),
	value(value) {
}


/** Overloads the operator << from std::ostream
 *
 */
std::ostream& operator<<(std::ostream &os, const Interest& self) {
	return os << 
		"{"
			"\"category\":\"" << self.category << "\","
			"\"value\":\"" << self.value << "\""
		"}";
}
