#include "TaskQueue.h"

TaskQueue::TaskQueue() : stopped(false), monitor(), taskQueue()
{
}

TaskQueue::~TaskQueue()
{
	monitor.Enter();
	cout<<"enter in critical section"<<endl;
    while(! taskQueue.empty())
    {
        Task t = Dequeue();
        t.Shutdown(SocketShutdown(Both));
        t.Close();
    }
    cout<<"leave from critical section"<<endl;
    monitor.Leave();
}

void TaskQueue::Enqueue(Task task)
{
    monitor.Enter();
    cout<<"enter in critical section"<<endl;
	if (!stopped)
		taskQueue.push(task);
	cout<<"leave from critical section"<<endl;
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
