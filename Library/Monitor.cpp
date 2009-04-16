#include "Monitor.h"

void Monitor::Enter()
{
	std::cout<<"Monitor::Enter"<<std::endl;
	int i = 40000;
	while (!mutex.TryLock() && i --> 0);
	if (i == -1)
		mutex.Lock();
}

void Monitor::Leave()
{
	std::cout<<"Monitor::Leave"<<std::endl;
	mutex.Unlock();
}

void Monitor::Wait()
{
	std::cout<<"Monitor::Wait"<<std::endl;
	int err = pthread_cond_wait(event.GetEvent(), mutex.GetMutex());
	if (err != 0)
		perror("error in Monitor Wait");
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
