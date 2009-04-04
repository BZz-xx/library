#include "Monitor.h"

Monitor::Monitor()
{
	mutex = new Mutex();
	event = new Event();
}

Monitor::~Monitor()
{
	delete mutex;
	delete event;
}

void Monitor::Enter()
{
	int i = 4000;
	while (!mutex->TryLock() && i --> 0);
	if (i == 0)
		mutex->Lock();
}

void Monitor::Leave()
{
	mutex->Unlock();
}

void Monitor::Wait()
{
	pthread_cond_wait(&event->GetEvent(), &mutex->GetMutex());
}

void Monitor::Pulse()
{
	event->Signal();
}

void Monitor::PulseAll()
{
	event->SignalAll();
}
