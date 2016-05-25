#include "SugestionsGenerator.h"

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

