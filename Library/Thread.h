#ifndef THREAD_H
#define THREAD_H

#include <iostream>
#include <string>
#include <stdlib.h>
#include <pthread.h>

class ThreadPoolServer;

using namespace std;

class Thread
{
//FIELDS
		pthread_t thread;
		int threadId;
		void * (*routine)(void *);
//METHOdS
	public:
		Thread(int name, void * (*function)(void *));
		~Thread();

	public:
		void Run(ThreadPoolServer* tps);
		void Stop();
};

#endif // THREAD_H
