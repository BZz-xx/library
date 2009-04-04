#include "SocketWrapper.h"


using namespace std;

SocketWrapper::SocketWrapper(int fdscrptr)
{
	sockid = fdscrptr;
}

SocketWrapper::SocketWrapper(int domain, int type, int protocol)
{
	sockid = socket(domain, type, protocol);
	if ( sockid < 0 )
		perror("socket Error: can not create Socket");
}

SocketWrapper::~SocketWrapper()
{
}

void SocketWrapper::Bind(sockaddr_in * addr)
{
	int err = bind(sockid, (SA*) addr, sizeof(*addr));
	if (err < 0)
		perror("error BIND");
}

void SocketWrapper::Listen(int maxConnection)
{
	int err = listen(sockid, maxConnection);
	if (err)
		perror("error LISTEN");
}

SocketWrapper * SocketWrapper::Accept()
{
	int connfd = accept(sockid, 0, 0);
	if (connfd < 0)
		perror("error ACCEPT");
	return new SocketWrapper(connfd);
}

int SocketWrapper::Receive(char* buffer, int length)
{
	int n = recv(sockid, buffer, length, 0);
	if ( n < 0 )
		perror("read error");
	else
		if (n > 0)
			buffer[n] = 0;
	return n;
}

int SocketWrapper::Receive(char* buffer, int offset, int length)
{
	int n = recv(sockid, buffer + offset, length, 0);
	if ( n < 0 )
		perror("read error");
	else
		if (n > 0)
			buffer[n + offset] = 0;
	return n;
}

void SocketWrapper::Send(char* buffer, int length)
{
	int err = send(sockid, buffer, length, 0);
	if (err == -1)
		perror("Send(char* buffer, int length)");
}

void SocketWrapper::Send(string str)
{
	int err = send(sockid, str.data(), str.length(), 0);
	if (err == -1)
		perror("Send(string str)");
}

void SocketWrapper::Shutdown(SocketShutdown how)
{
	int err = shutdown(sockid, how);
	if (err < 0)
	{
		perror("socket's Shutdown error");
		cerr << "shutdowning option is " <<how <<endl;
	}
}

void SocketWrapper::Close()
{
	int err = close(sockid);
	if (err < 0)
		perror("socket's Close error");
}
