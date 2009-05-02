#include "ThreadPoolServer.h"

using namespace std;

ThreadPoolServer::ThreadPoolServer(int portNum, string fName) :
	port(portNum), fileName(fName), handledStopReq(false), pool(POOLSIZE), listner(portNum)
{
}

ThreadPoolServer::~ThreadPoolServer()
{
}

void ThreadPoolServer::Run()
{
	listner.Listen();

	pool.Start(&TaskHandle, this);

	int countFD;

	while(!handledStopReq)
	{
		countFD = listner.Select();
//		cout<<"$$$$$$$$$$$$$$ There are "<<countFD<<" new incoming Tasks"<<endl;
		for (int i = 0; i < countFD; i++)
			taskQueue.Enqueue(Task(listner.Accept(), false));
	}

//	cout<<"###########Task establishing is finished"<<endl;

	pool.Stop();
}

void ThreadPoolServer::Stop()
{
//	cout<<"ThreadPoolServer::Stop"<<endl;
	handledStopReq = true;
	taskQueue.Stop();
	listner.Shutdown(SocketShutdown(Both));
	listner.Close();
}

void* ThreadPoolServer::TaskHandle(void* argv)
{
	ThreadPoolServer* tps = reinterpret_cast<ThreadPoolServer*>(argv);
//	cout << "TaskHandle" <<endl;
	while(!tps->handledStopReq)
	{
		Task tmpTask = tps->taskQueue.Dequeue();
		if(tmpTask.isStopTask())
			break;
		if( tps->SocketHandle(tmpTask) )
			tps->Stop();
	}
//	cout << "TaskHandle finished" <<endl;
	return 0;
}

bool ThreadPoolServer::SocketHandle(SocketWrapper sock)
{
//	cout<<"SocketHandle"<<endl;
	char buffer[MAXLINE + 1];
	bool hendlingResult = false;
	//Прочитали все данные из сокета и обработали их по мере поступления
    int n = 0, totalBytesRead = 0;
    while ((n = sock.Receive(buffer, MAXLINE) ) > 0)
	{
		totalBytesRead += n;
		DataHandle(buffer, n);
	}
	sock.Shutdown( SocketShutdown(Read) );
//	cout << "readed " << totalBytesRead << " bytes" << endl;
	//Проверка на StopRequest
	if (buffer[0]=='s' && buffer[1]=='t' && buffer[2]=='o' && buffer[3]=='p' )
	{
		cout << "STOP" << endl;
		hendlingResult = true;
	}
	//Так на всякий случай
	buffer [0] = '\n';
	buffer [1] = 0;
	DataHandle(buffer, 2);
	//Ответили клиенту
	sock.Send("Ok");
	sock.Shutdown( SocketShutdown(Write) );
	sock.Close();

	return hendlingResult;
}
/*
//on NET test
int ThreadPoolServer::DataHandle(char* Data, int count)
{
	return 0;
}
*/
//on HDD test
int ThreadPoolServer::DataHandle(char* Data, int count)
{
	srand ( time(NULL) );
	string fn = fileName;
	fn += rand() % 10 + 48;
	ofstream file ( fn.data(), fstream::app );
	if (file == NULL)
	{
		perror("file opening error");
		return -1;
	}
	else
		for (int i = 0; i < 10; i++)
			file << Data << flush;

	return 0;
}
/*
// on CPU test
int ThreadPoolServer::DataHandle(char* Data, int count)
{
	srand ( time(NULL) );

	int dataHash;
	for(int i = 0; i < count; i++)
		dataHash += Data[i]*Data[i+(rand()%3 - 1)*1024];
	return dataHash;
}
*/

