#ifndef MONITOR_H
#define MONITOR_H

#include "Mutex.h"
#include "Event.h"
#include <iostream>

class Monitor
{
//FIELDS
	private:
		static Mutex mutex;
		static Event event;
//METHODS
	public:
		static void Enter();
		static void Leave();
		static void Wait();
		static void Pulse();
		static void PulseAll();
};

#endif // MONITOR_H
