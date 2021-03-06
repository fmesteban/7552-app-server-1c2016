#ifndef WEB_SERVER_MATCHER_SUGESTIONSGENERATOR_H_
#define WEB_SERVER_MATCHER_SUGESTIONSGENERATOR_H_

/** Include area. */
#include <map>
#include <vector>
#include <list>
#include "Suggestion.h"
#include "UsersContainer.h"
#include "User.h"
#include "Database.h"
#include "distance.h"

#define MAXDISTANCE 25 //It's in Km

class SuggestionsGenerator {
private:
	UsersContainer& usersContainer;
	std::vector<Suggestion*> suggestions;
	float calculatePoints(User &userA, User &userB);
	bool loadSuggestions();
public:
	explicit SuggestionsGenerator(UsersContainer& usersContainer);
	~SuggestionsGenerator();

	std::list<int> getPossibleMatches(int user, int cant);
	std::list<int> getMatches(int user);
};

#endif
