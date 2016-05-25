#ifndef WEB_SERVER_MATCHER_MATCH_H_
#define WEB_SERVER_MATCHER_MATCH_H_

#include "User.h"

class Match {
private:
	User &userA;
	User &userB;
public:
	Match(User &userA, User &userB);
	~Match();
};

#endif
