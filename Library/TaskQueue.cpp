#include "TaskQueue.h"

TaskQueue::TaskQueue() : stopped(false), monitor(), taskQueue()
{
}

TaskQueue::~TaskQueue()
{
	monitor.Enter();
	cout<<"enter in critical section ~TaskQueue"<<endl;
    while(! taskQueue.empty())
    {
        Task t = Dequeue();
        t.Shutdown(SocketShutdown(Both));
        t.Close();
    }
    cout<<"exit from critical section ~TaskQueue"<<endl;
    monitor.Leave();
}

void TaskQueue::Enqueue(Task task)
{
    monitor.Enter();
    cout<<"enter in critical section Enqueue"<<endl;
	if (!stopped)
		taskQueue.push(task);
	cout<<"exit from critical section Enqueue"<<endl;
	monitor.Leave();
	monitor.PulseAll();
    //monitor.Pulse();
}

Task TaskQueue::Dequeue()
{
	monitor.Enter();
	cout<<"enter in critical section Dequeue"<<endl;
	while (taskQueue.empty() && !stopped)
		monitor.Wait();
	if (stopped)
	{
		monitor.Leave();
		return Task::getStopTask();
	}
	Task t = taskQueue.front();
	taskQueue.pop();
	cout<<"exit in critical section Dequeue"<<endl;
    monitor.Leave();
    monitor.PulseAll();
    return t;
}

void TaskQueue::Stop()
{
	stopped = true;
}
