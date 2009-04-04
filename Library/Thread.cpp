#include "Thread.h"
#include <iostream>

using namespace std;

Thread::Thread(string name, void * (*function)(void *)) : threadId(name)
{
	routine = function;
}

Thread::~Thread()
{
}

void Thread::Run()
{
	cout<<"Thread "<<threadId<<" started"<<endl;
	pthread_create(&thread, 0, routine, 0);
}

void Thread::Stop()
{
	int retval = -1;
	pthread_detach(thread);
	cout<<"Thread "<<threadId<<" closed"<<endl;
	pthread_exit(&retval);
}
