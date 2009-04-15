#include "ThreadPoolServer.h"

using namespace std;

ThreadPoolServer::ThreadPoolServer() :
	handleStopReq(false), pool(POOLSIZE), taskQueue(), fileName("qwerty"), listner(port)
{
}

ThreadPoolServer::~ThreadPoolServer()
{
	listner.Shutdown(SocketShutdown(Both));
	listner.Close();

	pool.Stop();
}

void ThreadPoolServer::Run()
{
	listner.Listen();

	pool.Start(&TaskHandle, this);

	while(!handleStopReq)
		taskQueue.Enqueue(Task(listner.Accept(), false));

	pool.Stop();
	taskQueue.Stop();
}

void* ThreadPoolServer::TaskHandle(void* argv)
{
	ThreadPoolServer* tps = reinterpret_cast<ThreadPoolServer*>(argv);
	cout << "TaskHandle" <<endl;
	while(!tps->handleStopReq)
	{
		Task tmpTask = tps->taskQueue.Dequeue();
		tps->SocketHandle(tmpTask);
		/*if(tmpTask.isStopTask())
			break;
		if( tps.SocketHandle(tmpTask) )
			tps.taskQueue.Enqueue(Task::getStopTask());*/
	}
}

int ThreadPoolServer::DataHandle(char* Data)
{
	cout<<Data<<flush;
	return 0;
	ofstream file ( fileName.data(), fstream::app );
	if (file == NULL)
	{
		perror("file opening error");
		return -1;
	}
	else
		file << Data << flush;

	return 0;
}

bool ThreadPoolServer::SocketHandle(SocketWrapper sock)
{
	cout<<"SocketHandle"<<endl;
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

