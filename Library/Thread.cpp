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
	int err = pthread_create(&thread, 0, routine, 0);
	if (err < 0)
		perror("Error Thread Run(ptread_create)");
}

void Thread::Stop()
{
	int retval = -1;
	int err = pthread_detach(thread);
	if (err < 0)
		perror("Error Thread Stop(ptread_detach)");
	cout<<"Thread "<<threadId<<" closed"<<endl;
	pthread_exit(&retval);
}
