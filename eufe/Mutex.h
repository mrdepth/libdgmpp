#pragma once
#ifndef DONT_USE_MUTEX
#include <pthread.h>
#endif

class Mutex
{
public:
	Mutex(void);
	virtual ~Mutex(void);
	void lock();
	void unlock();

	class ScopedLock
	{
	public:
		ScopedLock(Mutex& mutex): mutex_(mutex)
		{
			mutex_.lock();
		}
		~ScopedLock()
		{
			mutex_.unlock();
		}

	private:
		Mutex& mutex_;
	};

private:
#ifndef DONT_USE_MUTEX
	pthread_mutex_t mutex_;
#endif
};
