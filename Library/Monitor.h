#ifndef MONITOR_H
#define MONITOR_H

#include "Mutex.h"
#include "Event.h"

class Monitor
{
//FIELDS
	private:
		Mutex mutex;
		Event event;
//METHODS
	public:
		Monitor();
		~Monitor();

	public:
		void Enter();
		void Leave();
		void Wait();
		void Pulse();
		void PulseAll();
	private:
};

#endif // MONITOR_H
