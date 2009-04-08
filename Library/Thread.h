#ifndef THREAD_H
#define THREAD_H

#include <iostream>
#include <string>
#include <stdlib.h>
#include <pthread.h>

using namespace std;

class Thread
{
//FIELDS
		pthread_t thread;
		string threadId;
		void * (*routine)(void *);
//METHOdS
	public:
		Thread(string name, void * (*function)(void *));
		~Thread();

	public:
		void Run();
		void Stop();
};

#endif // THREAD_H
