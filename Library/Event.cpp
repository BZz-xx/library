#include "Event.h"

Event::Event()
{
	int err = pthread_cond_init(&event, 0);
	if (err < 0)
		perror("error in Event Constructor");
}

Event::~Event()
{
	int err = pthread_cond_destroy(&event);
	if (err < 0)
		perror("error in Event Destructor");
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
