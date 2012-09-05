#pragma once
#include <pthread.h>

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
	pthread_mutex_t mutex_;
};
