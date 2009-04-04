#ifndef TASKQUEUE_H
#define TASKQUEUE_H

#include "SocketWrapper.h"
#include "Monitor.h"
#include <queue>
#include <list>

class TaskQueue
{
//FIELDS
    private:
		bool stopped;
		Monitor * monitor;
        queue <SocketWrapper * , list <SocketWrapper * > > * taskQueue;

//METHODS
    public:
        TaskQueue();
        ~TaskQueue();

    public:
        void Enqueue(SocketWrapper * task);
        SocketWrapper * Dequeue();
};

#endif // TASKQUEUE_H
