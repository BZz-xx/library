#include "Task.h"

Task::Task(int sockId, bool isStopTask) : SocketWrapper(sockId), stopTask(isStopTask)
{
	//ctor
}

Task::Task(const SocketWrapper& sock, bool isStopTask) : SocketWrapper(sock), stopTask(isStopTask)
{
	cout<<"new incoming Task"<< endl;
}

Task::~Task()
{
	//dtor
}

Task Task::getStopTask()
{
	return Task(-1, true);
}

bool Task::isStopTask()
{
	return stopTask;
}
