#include "Listner.h"

Listner::Listner(int port) : SocketWrapper(AF_INET, SOCK_STREAM, IPPROTO_TCP)
{
	sockaddr_in servAddr = GetServerAddres(port);
	Bind(&servAddr);
}

Listner::~Listner()
{
	//dtor
}

sockaddr_in Listner::GetServerAddres(int port)
{
	sockaddr_in servAddr;
	memset (&servAddr, 0, sizeof(servAddr));

	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(port);

	return servAddr;
}
