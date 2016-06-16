#ifndef WEB_SERVER_MATCHER_SUGESTION_H_
#define WEB_SERVER_MATCHER_SUGESTION_H_

#include "User.h"
#include "Match.h"

class Suggestion {
private:
	User &userA;
	User &userB;
	bool AlikesB;
	bool BlikesA;
	bool _someoneDisliked;
public:
	Suggestion(User &userA, User &userB);
	bool isMatch();
	bool someoneDisliked();
	Match *generateMatch();
	int getAnotherID(User &requesterUser);
	~Suggestion();
};

#endif
