#include "SimpleServer.h"

#include <netinet/in.h>
#include <iostream>
#include <stdlib.h>

SimpleServer::SimpleServer(int port, char* file) : servSock(AF_INET, SOCK_STREAM, IPPROTO_TCP)
{
	this->port = port;
	memset (buffer, 0, sizeof(char) * (MAXLINE + 1));
	fileName = string(file);
}

SimpleServer::~SimpleServer()
{
}

sockaddr_in SimpleServer::GetServerAddres()
{
	sockaddr_in servAddr;
	memset (&servAddr, 0, sizeof(servAddr));

	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(port);

	return servAddr;
}

void SimpleServer::Run(int ( * Handler ) ( string, char*))
{
	sockaddr_in servAddr = GetServerAddres();
	servSock.Bind(&servAddr);
	servSock.Listen();

	bool handleStopReq = false;

	while(!handleStopReq)
	{
		int countFD = servSock.Select();
		for (int i = 0; i < countFD; i++)
		{
			SocketWrapper clntSock = servSock.Accept();
			handleStopReq = Handle(clntSock, Handler);
			clntSock.Close();
		}
	}

	servSock.Close();
}

bool SimpleServer::Handle(SocketWrapper sock, int (* Handler) (string, char*))
{
	bool hendlingResult = false;
	//Прочитали все данные из сокета и обработали их по мере поступления
    int n = 0, totalBytesRead = 0;
    while ((n = sock.Receive(buffer, MAXLINE) ) > 0)
	{
		totalBytesRead += n;
		Handler(fileName, buffer);
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
	Handler(fileName, buffer);
	//Ответили ответили клиенту
	sock.Send("Ok");
	sock.Shutdown( SocketShutdown(Write) );

	return hendlingResult;
}
