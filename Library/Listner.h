#ifndef LISTNER_H
#define LISTNER_H

#include "../Library/SocketWrapper.h"


class Listner : public SocketWrapper
{
//FIELDS
//METHODS
	public:
		Listner(int port);
		virtual ~Listner();

	private:
		sockaddr_in GetServerAddres(int port);
};

#endif // LISTNER_H
