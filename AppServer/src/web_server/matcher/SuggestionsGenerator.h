#ifndef WEB_SERVER_MATCHER_SUGESTIONSGENERATOR_H_
#define WEB_SERVER_MATCHER_SUGESTIONSGENERATOR_H_

#include <map>
#include "Suggestion.h"

class SugestionsGenerator {
private:
	std::map<int, std::map<int, Sugestion*>* > sugestions;
public:
	SugestionsGenerator();
	virtual ~SugestionsGenerator();

	std::list<int> getPossibleMatches(int user, int cant);
	std::list<int> getMatches(int user);
};

#endif
