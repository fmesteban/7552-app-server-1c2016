/** Include area. */
#include "Suggestion.h"


/*------------------------------------------------------------------------
 * 	Member Functions Implementations
 * ---------------------------------------------------------------------*/

/** Suggestion constructor.
 *
 * 	\param userA Is the user to be suggested to \userB.
 * 	\param userB Is the user to be suggested to \userA.
 */
Suggestion::Suggestion(User &userA, User &userB) :
	userA(userA),
	userB(userB) {
	AlikesB = false;
	BlikesA = false;
	_someoneDisliked = false;
	sentToA = false;
	sentToB = false;
}


/** Gets a refference to one of the users of the suggestion.
 *
 * 	\return A refference to user A.
 */
User &Suggestion::getUserA(){
	return userA;
}


/** Gets a refference to one of the users of the suggestion.
 *
 * 	\return A refference to user B.
 */
User &Suggestion::getUserB(){
	return userB;
}


/** Tells to suggestion that user A has put a like to user B.
 *
 *	\param value If true, the user A has put a like. If false,
 *	doesn't mean anything (user A didn't put like yet).
 */
void Suggestion::setAlikesB(bool value){
	AlikesB = value;
}


/** Tells to suggestion that user B has put a like to user A.
 *
 *	\param value If true, the user B has put a like. If false,
 *	doesn't mean anything (user B didn't put like yet).
 */
void Suggestion::setBlikesA(bool value){
	BlikesA = value;
}


/** Tells to suggestion that one user has put dislike to the another.
 *
 * 	\param value If true, one user has put dislike to the another,
 * 	If false, it doesn't mean anything (any user has put dislike yet).
 */
void Suggestion::setsomeoneDisliked(bool value){
	_someoneDisliked = value;
}


/** Asks suggestion if both users like each other.
 *
 * 	\return True if both users like each other, False otherwise.
 */
bool Suggestion::isMatch(){
	return (AlikesB && BlikesA && !_someoneDisliked);
}


/** Suggestion has two users. This function returns the id from the user
 * 	who was not passed as parameter.
 *
 * 	\param requesterUser Is the user from who I don't want to know the ID.
 */
int Suggestion::getAnotherID(User &requesterUser){
	if (userA.getID() == requesterUser.getID())
		return userB.getID();
	else
		return userA.getID();
}


/** Asks suggestion if some user has put dislike to the another.
 *
 *	\return True if someone has put dislike, False otherwise.
 */
bool Suggestion::someoneDisliked(){
	return _someoneDisliked;
}


/** Instantiates a Match object between the users from the suggestion.
 *
 * 	\return a ptr to the generated Match object, or NULL if they don't
 * 	like each other.
 */
Match *Suggestion::generateMatch(){
	if(isMatch())
		return new Match(userA, userB);
	else
		return NULL;
}


/** Marks the suggestion as disliked by one of the users.
 *
 */
void Suggestion::markAsDisliked(){
	_someoneDisliked = true;
}


/** Tells to suggestion that the user with \idSrc liked the user with \idDest.
 *
 *	\param idSrc Is the id from user who has put a like to the other.
 *	\param idDest Is the id from user liked by the another.
 */
void Suggestion::addLike(int idSrc, int idDest){
	if(userA.getID() == idSrc)
		AlikesB = true;
	else
		BlikesA = true;
}


/** Overloads the operator << from std::ostream
 *
 *	\param os Is the output stream.
 *	\param self Is the current instance of Suggestion.
 */
std::ostream& operator<<(std::ostream &os, const Suggestion& self) {
	return os << 
		"{"
			"\"userA\":\"" << self.userA.getID() << "\","
			"\"userB\":\"" << self.userB.getID() << "\","
			"\"AlikesB\":\"" << self.AlikesB << "\","
			"\"BlikesA\":\"" << self.BlikesA << "\","
			"\"_someoneDisliked\":\"" << self._someoneDisliked << "\","
			"\"sentToA\":\"" << self.sentToA << "\","
			"\"sentToB\":\"" << self.sentToB << "\""
		"}";
}


/** Tells to suggestion if it was seen by user A.
 *
 *	\param value. If true, the user A has seen the user B as suggestion,
 *	otherwise user A didn't.
 */
void Suggestion::setSentToA(bool value){
	sentToA = value;
}


/** Tells to suggestion if it was seen by user B.
 *
 *	\param value If true, the user B has seen the user A as suggestion,
 *	otherwise user B didn't.
 */
void Suggestion::setSentToB(bool value){
	sentToB = value;
}


/** Asks suggestion if it was seen by specified user.
 *
 *	\param user The user who I don't know if has received the suggestion.
 *
 *	\return True if \user received the suggestion, False otherwise.
 */
bool Suggestion::wasSentToUser(User &user){
	return (user == userA) ? sentToA : sentToB;
}


/** Tells to suggestion if it was seen by specified user.
 *
 *	\param user
 *	\param value If true, \user has seen the another as suggestion,
 *	otherwise \user didn't.
 */
void Suggestion::setWasSentToUser(User &user, bool value){
	if (user == userA)
		setSentToA(value);
	else
		setSentToB(value);
}

Suggestion::~Suggestion() {
}

