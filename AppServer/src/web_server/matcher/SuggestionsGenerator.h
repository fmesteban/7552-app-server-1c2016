#ifndef WEB_SERVER_MATCHER_SUGESTIONSGENERATOR_H_
#define WEB_SERVER_MATCHER_SUGESTIONSGENERATOR_H_

#include <map>
#include <list>
#include "Suggestion.h"
#include "UsersContainer.h"
#include "User.h"

class SuggestionsGenerator {
private:
	UsersContainer& usersContainer;
	std::list<Suggestion*> suggestions;
	float calculatePoints(User &userA, User &userB);
public:
	explicit SuggestionsGenerator(UsersContainer& usersContainer);
	~SuggestionsGenerator();

	std::list<int> getPossibleMatches(int user, int cant);
	std::list<int> getMatches(int user);
};

#endif
