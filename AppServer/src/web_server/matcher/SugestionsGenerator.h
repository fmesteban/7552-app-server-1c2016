#ifndef WEB_SERVER_MATCHER_SUGESTIONSGENERATOR_H_
#define WEB_SERVER_MATCHER_SUGESTIONSGENERATOR_H_

#include <map>
#include "Sugestion.h"

class SugestionsGenerator {
private:
	std::map<int, std::map<int, Sugestion*>* > sugestions;
public:
	SugestionsGenerator();
	virtual ~SugestionsGenerator();
};

#endif
