#include "TaskQueue.h"

TaskQueue::TaskQueue() : stopped(false), monitor(), taskQueue()
{
}

TaskQueue::~TaskQueue()
{
	monitor.Enter();
    while(! taskQueue.empty())
    {
        SocketWrapper s = Dequeue();
        s.Shutdown(SocketShutdown(Both));
        s.Close();
    }
    monitor.Leave();
}

void TaskQueue::Enqueue(SocketWrapper task)
{
    monitor.Enter();
	if (!stopped)
		taskQueue.push(task);
	monitor.Leave();
    monitor.PulseAll();
}

SocketWrapper TaskQueue::Dequeue()
{
	monitor.Enter();
	while (taskQueue.empty() && !stopped)
		monitor.Wait();
	if (stopped)
	{
		monitor.Leave();
		return SocketWrapper(InvalidSocket);
	}
	SocketWrapper sw = taskQueue.front();
	taskQueue.pop();
    monitor.Leave();
    return sw;
}
