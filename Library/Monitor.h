#ifndef MONITOR_H
#define MONITOR_H

#include "Mutex.h"
#include "Event.h"
#include <iostream>

class Monitor
{
//FIELDS
	private:
		Mutex mutex;
		Event event;
//METHODS
	public:
		void Enter();
		void Leave();
		void Wait();
		void Pulse();
		void PulseAll();
};

#endif // MONITOR_H
