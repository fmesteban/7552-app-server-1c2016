#ifndef WEB_SERVER_MATCHER_SUGESTIONSGENERATOR_H_
#define WEB_SERVER_MATCHER_SUGESTIONSGENERATOR_H_

#include <map>
#include <list>
#include "Suggestion.h"
#include "UsersContainer.h"
#include "User.h"

class SugestionsGenerator {
private:
	UsersContainer& usersContainer;
	std::list<Sugestion*> suggestions;
	float calculatePoints(const User &userA, const User &userB);
public:
	explicit SugestionsGenerator(UsersContainer& usersContainer);
	~SugestionsGenerator();

	std::list<int> getPossibleMatches(int user, int cant);
	std::list<int> getMatches(int user);
};

#endif
