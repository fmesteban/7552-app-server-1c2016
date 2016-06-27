/** Include area. */
#include "Interest.h"
#include <string>
#include <ostream>


/*------------------------------------------------------------------------
 * 	Member Functions Implementations
 * ---------------------------------------------------------------------*/

/** Interest constructor.
 *
 * 	\param category Is the category of the interest.
 * 	\param value Is a value possible for category.
 */
Interest::Interest(const std::string &category, const std::string &value) :
	category(category),
	value(value) {
}

/** Gets a the category of interest.
 *
 * 	\return A refference to the internal category string.
 */
std::string &Interest::getCategory(){
	return category;
}

/** Gets a the value of interest.
 *
 * 	\return A refference to the internal value string.
 */
std::string &Interest::getValue(){
	return value;
}

/** Overloads the operator << from std::ostream
 *
 *	\param os Is the output stream.
 *	\param self Is the current instance of Interest.
 */
std::ostream& operator<<(std::ostream &os, const Interest& self) {
	return os << 
		"{"
			"\"category\":\"" << self.category << "\","
			"\"value\":\"" << self.value << "\""
		"}";
}
