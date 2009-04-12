#include "ThreadPoolServer.h"

using namespace std;

ThreadPool ThreadPoolServer::pool = ThreadPool(ThreadPoolServer::POOLSIZE);
TaskQueue ThreadPoolServer::taskQueue = TaskQueue();
Listner ThreadPoolServer::listner = Listner(ThreadPoolServer::port);
string ThreadPoolServer::fileName = "qwerty";

ThreadPoolServer::ThreadPoolServer(int portNum, string name)
{
	fileName = name;
}

ThreadPoolServer::~ThreadPoolServer()
{
	listner.Shutdown(SocketShutdown(Both));
	listner.Close();

	pool.Stop();
}

void ThreadPoolServer::Run()
{
	pool.Start(&TaskHandle);

	listner.Listen();

	while(!handleStopReq)
	{
		taskQueue.Enqueue(Task(listner.Accept(), false));
	}
}

void* ThreadPoolServer::TaskHandle(void* argv)
{
	while(!handleStopReq)
	{
		Task tmpTask = taskQueue.Dequeue();
		if(tmpTask.isStopTask())
			break;
		if( SocketHandle(tmpTask) )
			taskQueue.Enqueue(Task::getStopTask());
	}
}

int ThreadPoolServer::DataHandle(char* Data)
{
	ofstream file ( fileName.data(), fstream::app );
	if (file == NULL)
	{
		perror("file opening error");
		return -1;
	}
	else
		file << Data << flush;

	file.close();
	return 0;
}

bool ThreadPoolServer::SocketHandle(SocketWrapper sock)
{
	char buffer[MAXLINE + 1];
	bool hendlingResult = false;
	//Прочитали все данные из сокета и обработали их по мере поступления
    int n = 0, totalBytesRead = 0;
    while ((n = sock.Receive(buffer, MAXLINE) ) > 0)
	{
		totalBytesRead += n;
		DataHandle(buffer);
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
	DataHandle(buffer);
	//Ответили клиенту
	sock.Send("Ok");
	sock.Shutdown( SocketShutdown(Write) );

	return hendlingResult;
}

