#include "SuggestionsGenerator.h"
#include <map>
#include <list>


SuggestionsGenerator::SuggestionsGenerator(UsersContainer& usersContainer) :
	usersContainer(usersContainer) {

	Log::instance()->append(
			"Building suggestions.",
			Log::INFO);

	bool suggestionsLoaded = loadSuggestions();
	if(!suggestionsLoaded){
		Log::instance()->append(
				"There was an error loading suggestions from RocksDB.",
				Log::INFO);
	}
	else {
		Log::instance()->append(
			"Loaded " + std::to_string(suggestions.size()) + " suggestions correctly from RocksDB.",
			Log::INFO);
	}
}

/**
 * Loads suggestiosns saved in DB
 */
bool SuggestionsGenerator::loadSuggestions(){
	std::string suggestions_str;

	usersContainer.getDB().getValue(std::string("suggestions"), suggestions_str);

	std::cerr << "Suggestions: " << suggestions_str << std::endl;

	/* Loads the request into a JSON Value object */
	Json::Value root;
	Json::Reader reader;
	bool parsingSuccessful = reader.parse(suggestions_str, root);
	if (!parsingSuccessful){
		Log::instance()->append(
				"JSON saved for suggestions is not correct.",
				Log::ERROR);
		return false;
	}

	/* Parse interests array */
	Json::Value& JSON_suggestions = root["suggestions"];
	Json::ValueConstIterator it = JSON_suggestions.begin();
	for (; it != JSON_suggestions.end(); ++it)
	{
		const Json::Value& suggestion = *it;
		std::string userA_str = suggestion.get("userA", "unavailable").asString();
		int userAID;
		std::stringstream(userA_str) >> userAID ? userAID : 0;
		std::string userB_str = suggestion.get("userB", "unavailable").asString();
		int userBID;
		std::stringstream(userB_str) >> userBID ? userBID : 0;
		std::string AlikesB = suggestion.get("AlikesB", "unavailable").asString();
		std::string BlikesA = suggestion.get("BlikesA", "unavailable").asString();
		std::string _someoneDisliked = suggestion.get("_someoneDisliked", "unavailable").asString();
		std::string sentToA = suggestion.get("sentToA", "unavailable").asString();
		std::string sentToB = suggestion.get("sentToB", "unavailable").asString();
		if(userA_str == "unavailable" ||
		   userB_str == "unavailable" ||
		   AlikesB == "unavailable" ||
		   BlikesA == "unavailable" ||
		   _someoneDisliked == "unavailable" )
			continue;

		User* userA = usersContainer.getUser(userAID);
		User* userB = usersContainer.getUser(userBID);

		if (userA == NULL || userB == NULL)
			continue;

		Suggestion* sug = new Suggestion(*userA, *userB);
		sug->setAlikesB(AlikesB == "1");
		sug->setBlikesA(BlikesA == "1");
		sug->setsomeoneDisliked(_someoneDisliked == "1");
		sug->setSentToA(sentToA == "1");
		sug->setSentToB(sentToB == "1");

		/* save suggestion */
		suggestions.push_back(sug);
	}
	return true;
}

SuggestionsGenerator::~SuggestionsGenerator(){
	std::string key("suggestions");
	std::ostringstream value;
	value << "{\"suggestions\":[";
	std::list<Suggestion*>::iterator iter = suggestions.begin();
	for(; iter != suggestions.end(); ++iter){
		value << **iter;
		delete *iter;
	}
	value << "]}";
	std::cout << "Suggestions to be saved on DB" << std::endl;
	std::cout << value.str() << std::endl;
	usersContainer.getDB().putKeyValue(key, value.str());
}


float SuggestionsGenerator::calculatePoints(User &userA, User &userB){
	if(!userA.couldMatch(userB))
		return -1;
	double distance = DistanceHelper::distanceEarth(userA.getLatitude(),
									userA.getLongitude(),
									userB.getLatitude(),
									userB.getLongitude());

	if (distance > MAXDISTANCE)
		return -1;

	int points = 1;

	for (auto interestA : userA.getInterests()){
		if (interestA->getCategory() == "sex")
			continue;
		for (auto interestB : userB.getInterests()){
			if (interestA->getCategory() == interestB->getCategory()){
				if(interestA->getValue() == interestB->getValue())
					points += 1;
			}
		}
	}

	return points;
}


/** Returns a list of possible matches for the user up to a maximum cant. The list
 *  contains only the ID of each other user that implies a match.
 */
std::list<int> SuggestionsGenerator::getPossibleMatches(int user, int cant) {
	std::list<int> result;

	Log::instance()->append(
		"Getting suggestions for user with id: " + std::to_string(user),
		Log::INFO);

	/* get the user from container */
	User *userRef = usersContainer.getUser(user);
	if (userRef == NULL)
		return result;

	/* load the suggestions shown to other user, but not to current */
	userRef->loadNotShownSuggestions(result);

	/* we will calculate "cant" suggestions */
	for (int i = 1; i <= cant; ++i){

		/* temporal values for best suggestion */
		User *currentBestSuggestedUser;
		float currentBestSuggestedUserPoints = 0;

		/* get some random users from container to be faster than O(NxN) */
		std::list<User*> randomUsers;
		usersContainer.getRandomUsers(randomUsers);

		/* for each users, calculate the suggestion points *
		 * save if better than current best */
		std::list<User*>::iterator randomUsersIter = randomUsers.begin();
		for (; randomUsersIter != randomUsers.end(); ++randomUsersIter){
			float points = calculatePoints(*userRef, **randomUsersIter);
			if (points >= currentBestSuggestedUserPoints){
				currentBestSuggestedUser = *randomUsersIter;
				currentBestSuggestedUserPoints = points;
			}
		}

		/* random list has just repeated suggestions */
		if (currentBestSuggestedUserPoints <= 0)
			continue;

		/* add the suggestion to result list (just the id) */
		/* note: here we will have "cant" pushes or less */
		result.push_back(currentBestSuggestedUser->getID());

		Log::instance()->append(
			"Suggesting user " + std::to_string(currentBestSuggestedUser->getID()) + " to the requester user: " + std::to_string(user) + ".",
			Log::INFO);

		/* save suggestion */
		Suggestion *s = new Suggestion(*userRef, *currentBestSuggestedUser);
		suggestions.push_back(s);
		userRef->addSuggestion(s);
		currentBestSuggestedUser->addSuggestion(s);
		s->setWasSentToUser(*userRef, true);
		s->setWasSentToUser(*currentBestSuggestedUser, false);

		Log::instance()->append("Suggestion saved.", Log::INFO);
	}

	return result;
}
