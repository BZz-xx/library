#ifndef SOCKETWRAPPER_H_
#define SOCKETWRAPPER_H_

#include <iostream>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/select.h>

#define	SA	struct sockaddr
#define InvalidSocket	-1

using namespace std;

enum SocketShutdown
{
	Read = 0,
	Write = 1,
	Both = 2
};

class SocketWrapper
{
//FIELDS
private:
	int sockid;

//METHODS
public:
	SocketWrapper(int domain, int type, int protocol);
	SocketWrapper(int fdscrtr);
	~SocketWrapper();

public:
	void Bind(sockaddr_in * addr);
	void Listen(int maxConnection = SOMAXCONN);
	SocketWrapper Accept();
	int Select(int microsec = 100);

	int Receive(char* buffer, int length);
	int Receive(char* buffer, int offset, int length);

	void Send(char* buffer, int length);
	void Send(string str);

	void Shutdown(SocketShutdown how);
	void Close();
};

#endif /*SOCKETWRAPPER_H_*/
