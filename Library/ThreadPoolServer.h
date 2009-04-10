#ifndef THREADPOOLSERVER_H
#define THREADPOOLSERVER_H

#include "../Library/SocketWrapper.h"
#include "../Library/Monitor.h"
#include "../Library/ThreadPool.h"
#include "../Library/Task.h"
#include "../Library/TaskQueue.h"
#include "../Library/Listner.h"
#include <iostream>

class ThreadPoolServer
{
//FIELDS
	Listner listner;
	ThreadPool pool;
	static TaskQueue taskQueue;
	int port;
	static bool handleStopReq;
	static const unsigned short POOLSIZE = 4;
	static const unsigned short LISTENQ = 1024;
	static const unsigned short MAXLINE = 4096;
	string fileName;
	char buffer[MAXLINE + 1];
	int ( * handle ) ( string, char*);
//METHODS
	public:
		ThreadPoolServer(int port, char* fileName);
		~ThreadPoolServer();

	public:
		void Run(int (*) (string, char* ));
	private:
		bool Handle(SocketWrapper sock);
		static void* TaskHandle(void* argv);
};

#endif // THREADPOOLSERVER_H
