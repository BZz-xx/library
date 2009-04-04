#include "TaskQueue.h"

TaskQueue::TaskQueue() : stopped(false)
{
	monitor = new Monitor();
    taskQueue = new queue <SocketWrapper * , list <SocketWrapper *> > ();
}

TaskQueue::~TaskQueue()
{
	monitor->Enter();
    while(! taskQueue->empty())
    {
        SocketWrapper * s = Dequeue();
        s->Shutdown(SocketShutdown(Both));
        s->Close();
        delete s;
    }
    delete taskQueue;
    monitor->Leave();
    delete monitor;
}

void TaskQueue::Enqueue(SocketWrapper * task)
{
    monitor->Enter();
	if (!stopped)
		taskQueue->push(task);
	monitor->Leave();
    monitor->PulseAll();
}

SocketWrapper * TaskQueue::Dequeue()
{
	SocketWrapper * sw;
	monitor->Enter();
	while (taskQueue->empty() && !stopped)
		monitor->Wait();
	if (stopped)
	{
		monitor->Leave();
		return new SocketWrapper(InvalidSocket);
	}
	sw = taskQueue->front();
	taskQueue->pop();
    monitor->Leave();
    monitor->PulseAll();
    return sw;
}
