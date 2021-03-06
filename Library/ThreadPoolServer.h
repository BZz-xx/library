#ifndef THREADPOOLSERVER_H
#define THREADPOOLSERVER_H

#include "SocketWrapper.h"
#include "ThreadPool.h"
#include "Task.h"
#include "TaskQueue.h"
#include "Listner.h"
#include <iostream>
#include <fstream>

#include <stdlib.h>
#include <time.h>

using namespace std;
class ThreadPoolServer
{
//FIELDS
	Listner listner;
	ThreadPool pool;
	TaskQueue taskQueue;
	int port;
	bool handledStopReq;
	static const unsigned short POOLSIZE = 8;
	static const unsigned short LISTENQ = 1024;
	static const unsigned short MAXLINE = 4096;
	string fileName;
//METHODS

	public:
		ThreadPoolServer(int portNum, string fName);
		~ThreadPoolServer();

	public:
		void Run();
	private:
		static void* TaskHandle(void* argv);
		bool SocketHandle(SocketWrapper sock);
		int DataHandle (char* Data, int count);
		void Stop();
//NO MORE COPYING OBJECTS
		ThreadPoolServer ( const ThreadPoolServer& );
		void operator = ( const ThreadPoolServer& );
};

#endif // THREADPOOLSERVER_H
