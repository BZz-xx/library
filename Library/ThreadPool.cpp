#include "ThreadPool.h"

ThreadPool::ThreadPool(int volume) : capacity(volume)
{
	//ctor
}

ThreadPool::~ThreadPool()
{
	while(!pool.empty())
	{
		Thread* t = pool.back();
		pool.pop_back();
		t->Stop();
		delete t;
	}
}

void ThreadPool::Start(void * (*onRequest)(void * argv))
{
	for(int i = 0; i < capacity; ++i)
	{
		pool.push_back(new Thread("", onRequest));
		pool.back()->Run();
	}
}

void ThreadPool::Stop()
{
	for(int i = 0; i < capacity; ++i)
	{
		Thread* t = pool.back();
		pool.pop_back();
		t->Stop();
		delete t;
	}
}
