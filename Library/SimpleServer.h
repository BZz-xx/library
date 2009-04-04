#ifndef SIMPLESERVER_H_
#define SIMPLESERVER_H_

#include "SocketWrapper.h"
#include "Listner.h"

class SimpleServer
{
//FIELDS
private:
	SocketWrapper * servSock;
	int port;
	static const unsigned short LISTENQ = 1024;
	static const unsigned short MAXLINE = 4096;
	string fileName;
	char buffer[MAXLINE + 1];

//METHODS
public:
	SimpleServer(int port, char* fileName);
	~SimpleServer();

public:
	void Run(int (*) (string, char* ));
	sockaddr_in GetServerAddres();

private:
	bool Handle(SocketWrapper* clntSock, int (*) (string, char* ));
};

#endif /*SIMPLESERVER_H_*/
