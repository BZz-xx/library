#include "ThreadPoolServer.h"

ThreadPoolServer::ThreadPoolServer(int port, char* fileName) : handleStopReq(false)
{
	listner = new Listner(port);
	pool = new ThreadPool(POOLSIZE);
	taskQueue = new TaskQueue();
}

ThreadPoolServer::~ThreadPoolServer()
{
	listner->Shutdown(SocketShutdown(Both));
	listner->Close();
	delete listner;

	pool->Stop();
	delete pool;

	delete taskQueue;
}

void ThreadPoolServer::Run(int ( * Handler ) ( string, char*))
{
	//threadPool->Start();
	listner->Listen();

	while(!handleStopReq)
	{
		SocketWrapper * clntSock = listner->Accept();
		taskQueue->Enqueue(clntSock);
	}
}

/*
bool ThreadPoolServer::Handle(int (* Handler) (string, char*))
{
	return fasle;
}
*/
