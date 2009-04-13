#ifndef THREADPOOL_H
#define THREADPOOL_H

#include "Thread.h"
#include <list>

class ThreadPoolServer;

class ThreadPool
{
//FIELDS
	int capacity;
	list<Thread> pool;
//METHODS
	public:
		ThreadPool(int volume);
		~ThreadPool();

	public:
		void Start(void * (*Routine)(void *), ThreadPoolServer* tps);
		void Stop();
};

#endif // THREADPOOL_H
