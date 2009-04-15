#ifndef THREADPOOLSERVER_H
#define THREADPOOLSERVER_H

#include "SocketWrapper.h"
#include "ThreadPool.h"
#include "Task.h"
#include "TaskQueue.h"
#include "Listner.h"
#include <iostream>
#include <fstream>

using namespace std;
class ThreadPoolServer
{
//FIELDS
	Listner listner;
	ThreadPool pool;
	TaskQueue taskQueue;
	static const int port = 10080;
	bool handleStopReq;
	static const unsigned short POOLSIZE = 4;
	static const unsigned short LISTENQ = 1024;
	static const unsigned short MAXLINE = 4096;
	string fileName;
//METHODS

	public:
		ThreadPoolServer();
		~ThreadPoolServer();

	public:
		void Run();
	private:
		static void* TaskHandle(void* argv);
		bool SocketHandle(SocketWrapper sock);
		int DataHandle (char* Data);
		void Stop();
//NO MORE COPYING OBJECTS
		ThreadPoolServer ( const ThreadPoolServer& );
		void operator = ( const ThreadPoolServer& );
};

#endif // THREADPOOLSERVER_H
