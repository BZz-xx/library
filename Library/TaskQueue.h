#ifndef TASKQUEUE_H
#define TASKQUEUE_H

#include "Task.h"
#include "Monitor.h"
#include <queue>
#include <list>

class TaskQueue
{
//FIELDS
    private:
		bool stopped;
        queue <Task, list <Task> > taskQueue;

//METHODS
    public:
        TaskQueue();
        ~TaskQueue();

    public:
        void Enqueue(Task task);
        void Stop();
        Task Dequeue();
};

#endif // TASKQUEUE_H
