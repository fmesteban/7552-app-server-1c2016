/** Include area. */
#include "Thread.h"
#include <pthread.h>


/*------------------------------------------------------------------------
 * 	Member Functions Implementations
 * ---------------------------------------------------------------------*/

/** Static function that casts the Thread instance and runs its run() function.
 *
 *	\param data Is a pointer to a instance of Thread.
 */
static void* starter(void* data){
	Thread* self = (Thread*) data;
	self->run();
	return NULL;
}


/** Starts the thread, running the run() function.
 *
 */
void Thread::start(){
	pthread_create(&thread, NULL, starter, (void*)this);
}


/** Waits the end of run() function and joins the thread.
 *
 */
void Thread::join(){
	pthread_join(*(unsigned long int*)this->thread, NULL);
}


Thread::~Thread(){
}
