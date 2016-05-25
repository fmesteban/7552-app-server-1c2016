#ifndef THREAD_H_
#define THREAD_H_

#include <pthread.h>

/** pthread Wrapper
 * 	User must inherit from Thread, and implement run function.
 */
class Thread {
private:
	pthread_t thread;

public:
	/* Starts the thread */
	void start();
	/* Joins the thread */
	void join();
	/* Internal thrad function. User must define it */
	virtual void run() = 0;

	virtual ~Thread();
};

#endif
