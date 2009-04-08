#include "ThreadPool.h"

ThreadPool::ThreadPool(int volume) : capacity(volume), pool()
{
}

ThreadPool::~ThreadPool()
{
	while(!pool.empty())
	{
		Thread t = pool.back();
		pool.pop_back();
		t.Stop();
	}
}

void ThreadPool::Start(void * (*Routine)(void * argv))
{
	for(int i = 0; i < capacity; ++i)
	{
		pool.push_back(Thread("", Routine));
		pool.back().Run();
	}
}

void ThreadPool::Stop()
{
	for(int i = 0; i < capacity; ++i)
	{
		Thread t = pool.back();
		pool.pop_back();
		t.Stop();
	}
}
