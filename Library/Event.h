#ifndef EVENT_H
#define EVENT_H

#include <iostream>
#include <pthread.h>

typedef pthread_cond_t EventType;

class Event
{
//FIELDS
	EventType event;
//METHODS
	public:
		Event();
		~Event();

	public:
		EventType GetEvent();
		void Signal();
		void SignalAll();
};

#endif // EVENT_H
