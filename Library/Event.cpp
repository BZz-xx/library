#include "Event.h"

Event::Event()
{
	pthread_cond_init(&event, 0);
}

Event::~Event()
{
	pthread_cond_destroy(&event);
}

EventType Event::GetEvent()
{
	return event;
}

void Event::Signal()
{
	pthread_cond_signal(&event);
}

void Event::SignalAll()
{
	pthread_cond_broadcast(&event);
}
