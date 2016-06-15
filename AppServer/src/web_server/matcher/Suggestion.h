#ifndef WEB_SERVER_MATCHER_SUGESTION_H_
#define WEB_SERVER_MATCHER_SUGESTION_H_

#include "User.h"
#include "Match.h"

class Sugestion {
private:
	User &userA;
	User &userB;
	bool AlikesB;
	bool BlikesA;
	bool _someoneDisliked;
public:
	Sugestion(User &userA, User &userB);
	bool isMatch();
	bool someoneDisliked();
	Match *generateMatch();
	int getAnotherID(User &requesterUser);
	~Sugestion();
};

#endif
