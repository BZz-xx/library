#include "TaskQueue.h"

TaskQueue::TaskQueue() : stopped(false), taskQueue()
{
}

TaskQueue::~TaskQueue()
{
	Monitor::Enter();
	cout<<"enter in critical section ~TaskQueue"<<endl;
    while(! taskQueue.empty())
    {
        Task t = Dequeue();
        t.Shutdown(SocketShutdown(Both));
        t.Close();
    }
    cout<<"exit from critical section ~TaskQueue"<<endl;
    Monitor::Leave();
}

void TaskQueue::Enqueue(Task task)
{
    Monitor::Enter();
    cout<<"enter in critical section Enqueue"<<endl;
	if (!stopped)
		taskQueue.push(task);
	cout<<">>>There are "<<taskQueue.size()<<" task in TaskQueue"<<endl;
	cout<<"exit from critical section Enqueue"<<endl;
	Monitor::Leave();
	Monitor::PulseAll();
}

Task TaskQueue::Dequeue()
{
	Monitor::Enter();
	cout<<"enter in critical section Dequeue"<<endl;
	while (taskQueue.empty() && !stopped)
	{
		cout<<"no tasks exists. exit from critical section Dequeue. Wait"<<endl;
		Monitor::Leave();
		Monitor::Wait();
	}
	if (stopped)
	{
		Monitor::Leave();
		return Task::getStopTask();
	}
	Task t = taskQueue.front();
	taskQueue.pop();
	cout<<"exit from critical section Dequeue"<<endl;
    Monitor::Leave();
    Monitor::PulseAll();
    return t;
}

void TaskQueue::Stop()
{
	stopped = true;
}
