#include "TaskQueue.h"

TaskQueue::TaskQueue() : stopped(false), monitor(), taskQueue()
{
}

TaskQueue::~TaskQueue()
{
	monitor.Enter();
    while(! taskQueue.empty())
    {
        Task t = Dequeue();
        t.Shutdown(SocketShutdown(Both));
        t.Close();
    }
    monitor.Leave();
}

void TaskQueue::Enqueue(Task task)
{
    monitor.Enter();
	if (!stopped)
		taskQueue.push(task);
	monitor.Leave();
    monitor.PulseAll();
}

Task TaskQueue::Dequeue()
{
	monitor.Enter();
	while (taskQueue.empty() && !stopped)
		monitor.Wait();
	if (stopped)
	{
		monitor.Leave();
		return Task::getStopTask();
	}
	Task t = taskQueue.front();
	taskQueue.pop();
    monitor.Leave();
    return t;
}

void TaskQueue::Stop()
{
	stopped = true;
}
