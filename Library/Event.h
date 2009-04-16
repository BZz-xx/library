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
		EventType* GetEvent();
		void Signal();
		void SignalAll();
	private:
//NO MORE COPYING OBJECTS
		Event ( const Event& );
		void operator = ( const Event& );
};

#endif // EVENT_H
