#ifndef THREADPOOLSERVER_H
#define THREADPOOLSERVER_H

#include "../Library/SocketWrapper.h"
#include "../Library/Monitor.h"
#include "../Library/ThreadPool.h"
#include "../Library/Task.h"
#include "../Library/TaskQueue.h"
#include "../Library/Listner.h"
#include <iostream>

using namespace std;
class ThreadPoolServer
{
//FIELDS
	static Listner listner;
	static ThreadPool pool;
	static TaskQueue taskQueue;
	static const int port = 10080;
	static bool handleStopReq;
	static const unsigned short POOLSIZE = 4;
	static const unsigned short LISTENQ = 1024;
	static const unsigned short MAXLINE = 4096;
	static string fileName;
//METHODS
//static constructor. WTF??
/*
Compiling: ThreadPoolServer.cpp
In file included from /root/library/Library/ThreadPoolServer.cpp:1:
/root/library/Library/ThreadPoolServer.h:26: error: constructor cannot be static member function
*/
	public:
		ThreadPoolServer(int port, string name);
		~ThreadPoolServer();

	public:
		static void Run();
	private:
		static void* TaskHandle(void* argv);
		static bool SocketHandle(SocketWrapper sock);
		static int DataHandle (char* Data);
};

#endif // THREADPOOLSERVER_H
