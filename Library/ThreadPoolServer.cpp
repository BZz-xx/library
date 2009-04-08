#include "ThreadPoolServer.h"

ThreadPoolServer::ThreadPoolServer(int port, char* fileName) : handleStopReq(false), listner(port), pool(POOLSIZE), taskQueue()
{
}

ThreadPoolServer::~ThreadPoolServer()
{
	listner.Shutdown(SocketShutdown(Both));
	listner.Close();

	pool.Stop();
}

void ThreadPoolServer::Run(int ( * Handler ) ( string, char*))
{
	//threadPool->Start();
	listner.Listen();

	while(!handleStopReq)
	{
		SocketWrapper clntSock = listner.Accept();
		taskQueue.Enqueue(clntSock);
	}
}

/*
bool ThreadPoolServer::Handle(int (* Handler) (string, char*))
{
	return fasle;
}
*/
