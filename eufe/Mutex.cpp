#include "Mutex.h"

Mutex::Mutex(void)
{
	pthread_mutexattr_t attr;
	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&mutex_, &attr);
}

Mutex::~Mutex(void)
{
	pthread_mutex_destroy(&mutex_);
}

void Mutex::lock()
{
	pthread_mutex_lock(&mutex_);
}

void Mutex::unlock()
{
	pthread_mutex_unlock(&mutex_);
}