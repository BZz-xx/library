#ifndef THREADPOOLSERVER_H
#define THREADPOOLSERVER_H

#include "../Library/SocketWrapper.h"
#include "../Library/Monitor.h"
#include "../Library/ThreadPool.h"
#include "../Library/TaskQueue.h"
#include "../Library/Listner.h"

class ThreadPoolServer
{
//FIELDS
	Listner* listner;
	ThreadPool* pool;
	TaskQueue* taskQueue;
	int port;
	bool handleStopReq;
	static const unsigned short POOLSIZE = 4;
	static const unsigned short LISTENQ = 1024;
	static const unsigned short MAXLINE = 4096;
	string fileName;
	char buffer[MAXLINE + 1];
//METHODS
	public:
		ThreadPoolServer(int port, char* fileName);
		~ThreadPoolServer();

	public:
		void Run(int (*) (string, char* ));
	private:
		bool Handle(SocketWrapper* clntSock, int (*) (string, char* ));
};

#endif // THREADPOOLSERVER_H
