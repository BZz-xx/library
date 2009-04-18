#include "Thread.h"
#include <iostream>

using namespace std;

Thread::Thread(int name, void * (*function)(void *)) : threadId(name)
{
	routine = function;
}

Thread::~Thread()
{
}

void Thread::Run(ThreadPoolServer* tps)
{
	cout<<"Thread "<<threadId<<" started"<<endl;
	int err = pthread_create(&thread, 0, routine, tps);
	if (err < 0)
		perror("Error Thread Run(ptread_create)");
}

void Thread::Stop()
{
	int err = pthread_detach(thread);
	if (err < 0)
		perror("Error Thread Stop(ptread_detach)");
	err = pthread_cancel(thread);
	if (err != 0)
		perror("Error Thread Stop(pthread_cancel)");
	cout<<"Thread "<<threadId<<" closed"<<endl;
}
