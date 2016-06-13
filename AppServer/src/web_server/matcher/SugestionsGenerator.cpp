#include "SugestionsGenerator.h"
#include <map>

SugestionsGenerator::SugestionsGenerator() {
}

SugestionsGenerator::~SugestionsGenerator() {
	std::map<int,std::map<int, Sugestion*>* >::iterator it = sugestions.begin();
	for(; it != sugestions.end(); ++it){
		std::map<int, Sugestion*>::iterator itS = it->second->begin();
		for(; itS != it->second->end(); ++itS){
			delete itS->second;
		}
		delete it->second;
	}
}

/** Returns a list of possible matches for the user up to a maximum cant. The list
 *  contains only the ID of each other user that implies a match.
 */
std::list<int> SugestionsGenerator::getPossibleMatches(int user, int cant) {

}

/** Returns a list of matches for the user. The list
 *  contains only the ID of each other user that implies a match.
 */
std::list<int> SugestionsGenerator::getMatches(int user) {

}