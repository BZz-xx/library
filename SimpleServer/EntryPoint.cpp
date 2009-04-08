#include <iostream>
#include <fstream>
#include "../Library/SimpleServer.h"

using namespace std;

int WriteDataToFile(string FileName, char* Data)
{
	ofstream file ( FileName.data(), fstream::app );
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

int main( int argc, char** argv )
{
	if (argc < 3)
	{
		cerr << "usage: ./Server portNum filename" << endl;
                return -1;
	}

    int Port = atoi ( argv [ 1 ] );
	char* fileName = argv[2];

	SimpleServer server = SimpleServer(Port, fileName);
	server.Run( &WriteDataToFile);

	return 0;
}
