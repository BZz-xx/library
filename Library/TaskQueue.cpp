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
	cout<<">>>There are "<<taskQueue.size()<<" task in TaskQueue"<<endl;
	cout<<"exit from critical section Enqueue"<<endl;
	monitor.PulseAll();
//	monitor.Pulse();
	monitor.Leave();
}

Task TaskQueue::Dequeue()
{
	monitor.Enter();
	cout<<"enter in critical section Dequeue"<<endl;
	while (taskQueue.size() == 0 && !stopped)
	{
		cout<<"no tasks exists. Waiting in critical section Dequeue."<<endl;
		monitor.Wait();
	}
	if (stopped)
	{
		monitor.Leave();
		return Task::getStopTask();
	}
	Task t = taskQueue.front();
	taskQueue.pop();
	cout<<"exit from critical section Dequeue"<<endl;
    monitor.Leave();
    return t;
}

void TaskQueue::Stop()
{
	monitor.Enter();
	stopped = true;
	monitor.Leave();
}
