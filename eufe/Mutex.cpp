#include "Mutex.h"

Mutex::Mutex(void)
{
#ifndef DONT_USE_MUTEX
	pthread_mutexattr_t attr;
	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&mutex_, &attr);
#endif
}

Mutex::~Mutex(void)
{
#ifndef DONT_USE_MUTEX
	pthread_mutex_destroy(&mutex_);
#endif
}

void Mutex::lock()
{
#ifndef DONT_USE_MUTEX
	pthread_mutex_lock(&mutex_);
#endif
}

void Mutex::unlock()
{
#ifndef DONT_USE_MUTEX
	pthread_mutex_unlock(&mutex_);
#endif
}