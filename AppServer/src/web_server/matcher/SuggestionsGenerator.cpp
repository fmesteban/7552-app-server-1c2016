#include "SuggestionsGenerator.h"
#include <map>
#include <list>


SuggestionsGenerator::SuggestionsGenerator(UsersContainer& usersContainer) :
	usersContainer(usersContainer) {
}


SuggestionsGenerator::~SuggestionsGenerator(){
	std::list<Suggestion*>::iterator iter = suggestions.begin();
	for(; iter != suggestions.end(); ++iter)
		delete *iter;
}


float SuggestionsGenerator::calculatePoints(User &userA, User &userB){
	if(!userA.couldMatch(userB)){
		return -1;
	}

	return 0;
}


/** Returns a list of possible matches for the user up to a maximum cant. The list
 *  contains only the ID of each other user that implies a match.
 */
std::list<int> SuggestionsGenerator::getPossibleMatches(int user, int cant) {
	std::list<int> result;

	/* get the user from container */
	User *userRef = usersContainer.getUser(user);
	if (userRef == NULL)
		return result;

	/* we will calculate "cant" suggestions */
	for (int i = 1; i < cant; ++i){
		/* temporal values for best suggestion */
		User *currentBestSuggestedUser;
		float currentBestSuggestedUserPoints = 0;

		/* get some random users from container for be faster than O(NxN) */
		std::list<User*> randomUsers;
		usersContainer.getRandomUsers(randomUsers);

		/* for each users, calculate the suggestion points *
		 * save if better than current best */
		std::list<User*>::iterator randomUsersIter = randomUsers.begin();
		for (; randomUsersIter != randomUsers.end(); ++randomUsersIter){
			float points = calculatePoints(*userRef, **randomUsersIter);
			if (points > currentBestSuggestedUserPoints){
				currentBestSuggestedUser = *randomUsersIter;
				currentBestSuggestedUserPoints = points;
			}
		}

		/* random list has just repeated suggestions */
		if (currentBestSuggestedUserPoints < 0)
			continue;

		/* add the suggestion to result list (just the id) */
		/* note: here we will have "cant" pushes or less */
		result.push_back(currentBestSuggestedUser->getID());

		/* save suggestion */
		suggestions.push_back(new Suggestion(*userRef, *currentBestSuggestedUser));
	}

	return result;
}

/** Returns a list of matches for the user. The list
 *  contains only the ID of each other user that implies a match.
 */
std::list<int> SuggestionsGenerator::getMatches(int user) {
}
