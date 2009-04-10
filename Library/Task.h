#ifndef TASK_H
#define TASK_H

#include "../Library/SocketWrapper.h"


class Task : public SocketWrapper
{
//FIELDS
private:
	bool stopTask;

//METHODS
	public:
		Task(int sockId, bool isStopTask);
		Task(const SocketWrapper& sock, bool isStopTask);
		~Task();

	public:
		static Task getStopTask();
		bool isStopTask();
};

#endif // TASK_H
