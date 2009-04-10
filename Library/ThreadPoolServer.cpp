#include "ThreadPoolServer.h"

ThreadPoolServer::ThreadPoolServer(int port, char* fileName) : listner(port), pool(POOLSIZE)
{
	handleStopReq = false;
}

ThreadPoolServer::~ThreadPoolServer()
{
	listner.Shutdown(SocketShutdown(Both));
	listner.Close();

	pool.Stop();
}

void ThreadPoolServer::Run(int ( * tHandle ) ( string, char*))
{
	handle = tHandle;

	pool.Start(&TaskHandle);

	listner.Listen();

	while(!handleStopReq)
	{
		taskQueue.Enqueue(Task(listner.Accept(), false));
	}
}

void* ThreadPoolServer::TaskHandle(void* argv)
{
	while(1)
	{
		Task tmpTask = taskQueue.Dequeue();
		if(tmpTask.isStopTask())
			break;
		handleStopReq = Handle(tmpTask);
	}
}

bool ThreadPoolServer::Handle(SocketWrapper sock)
{
	bool hendlingResult = false;
	//Прочитали все данные из сокета и обработали их по мере поступления
    int n = 0, totalBytesRead = 0;
    while ((n = sock.Receive(buffer, MAXLINE) ) > 0)
	{
		totalBytesRead += n;
		(*handle)(fileName, buffer);
	}
	sock.Shutdown( SocketShutdown(Read) );
	cout << "readed " << totalBytesRead << " bytes" << endl;
	//Проверка на StopRequest
	if (buffer[0]=='s' && buffer[1]=='t' && buffer[2]=='o' && buffer[3]=='p' )
	{
		cout << "STOP" << endl;
		hendlingResult = true;
	}
	//Так на всякий случай
	buffer [0] = '\n';
	buffer [1] = 0;
	handle(fileName, buffer);
	//Ответили ответили клиенту
	sock.Send("Ok");
	sock.Shutdown( SocketShutdown(Write) );

	return hendlingResult;
}

