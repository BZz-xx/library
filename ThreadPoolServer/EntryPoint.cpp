#include <iostream>
#include <fstream>

#include <gtest/gtest.h>
#include "../Library/Mutex.h"
#include "../Library/ThreadPoolServer.h"
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

TEST(Mutex, TestOne)
{
	Mutex m;
	m.Lock();
	ASSERT_EQ(false, m.TryLock());
	m.Unlock();
	ASSERT_EQ(true, m.TryLock());
	ASSERT_EQ(false, m.TryLock());
	m.Unlock();
}

class Lockable
{
	Mutex m;
	void Lock(){m.Lock();}
	void Unlock(){m.Unlock();}
	bool TryLock(){return m.TryLock();}

	friend void lock(Lockable& obj);
	friend void unlock(Lockable& obj);
	friend bool tryLock(Lockable& obj);
};

void lock(Lockable& obj){obj.Lock();};
void unlock(Lockable& obj){obj.Unlock();};
bool tryLock(Lockable& obj){return obj.TryLock();};

class TestLockable : public Lockable
{
};

TEST(LockableObject, test1)
{
	TestLockable obj;
	lock(obj);
	ASSERT_EQ(false,tryLock(obj));
	unlock(obj);
	ASSERT_EQ(true,tryLock(obj));
	ASSERT_EQ(false,tryLock(obj));
	unlock(obj);
}

int main( int argc, char** argv )
{

	/*::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
	if (argc < 3)
	{
		cerr << "usage: ./Server portNum filename" << endl;
                return -1;
	}

    int Port = atoi ( argv [ 1 ] );
	char* fileName = argv[2];*/

	ThreadPoolServer tps = ThreadPoolServer();
	tps.Run();

	return 0;
}
