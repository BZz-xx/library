#include "Event.h"

Event::Event()
{
	int err = pthread_cond_init(&event, NULL);
	if (err != 0)
		perror("error in Event Constructor");
//	event = PTHREAD_COND_INITIALIZER;
}

Event::~Event()
{
	int err = pthread_cond_destroy(&event);
	if (err != 0)
		perror("error in Event Destructor");
}

EventType* Event::GetEvent()
{
	return &event;
}

void Event::Signal()
{
	int err = pthread_cond_signal(&event);
	if (err != 0)
		perror("error in Event Signal");
}

void Event::SignalAll()
{
	int err = pthread_cond_broadcast(&event);
	if (err != 0)
		perror("error in Event Signal");
}
