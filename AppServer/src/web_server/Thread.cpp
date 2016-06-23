/** Include area. */
#include "Thread.h"
#include <pthread.h>

static void* starter(void* data){
	Thread* self = (Thread*) data;
	self->run();
	return NULL;
}

void Thread::start(){
	pthread_create(&thread, NULL, starter, (void*)this);
}

void Thread::join(){
	pthread_join(*(unsigned long int*)this->thread, NULL);
}

Thread::~Thread(){
}
