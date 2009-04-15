#include "Monitor.h"

Mutex Monitor::mutex = Mutex();
Event Monitor::event = Event();

void Monitor::Enter()
{
	int i = 4000;
	while (!mutex.TryLock() && i --> 0);
	if (i == 0)
		mutex.Lock();
}

void Monitor::Leave()
{
	mutex.Unlock();
}

void Monitor::Wait()
{
	std::cout<<"Monitor::Wait"<<std::endl;
	pthread_cond_wait(&(event.GetEvent()), &(mutex.GetMutex()));
}

void Monitor::Pulse()
{
	std::cout<<"Monitor::Pulse"<<std::endl;
	event.Signal();
}

void Monitor::PulseAll()
{
	std::cout<<"Monitor::PulseAll"<<std::endl;
	event.SignalAll();
}
