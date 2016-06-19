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
	User &getUserA();
	User &getUserB();
	bool someoneDisliked();
	Match *generateMatch();
	int getAnotherID(User &requesterUser);
	void markAsDisliked();
	void addLike(int idSrc, int idDest);
	void setAlikesB(bool value);
	void setBlikesA(bool value);
	void setsomeoneDisliked(bool value);
	friend std::ostream & operator<<(std::ostream &os, const Suggestion& self);
	~Suggestion();
};

#endif
