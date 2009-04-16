#include <iostream>
#include <fstream>

#include <gtest/gtest.h>
#include "../Library/Mutex.h"
#include "../Library/Thread.h"
#include "../Library/ThreadPoolServer.h"

#include <pthread.h>
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

class WS
{
	static pthread_mutex_t count_lock;
	static pthread_cond_t count_nonzero;
public:
	static unsigned count;

	static void* decrement_count(void* argv) {
	  pthread_mutex_lock(&count_lock);
	  while (count == 0)
	  {
	  	cout<<"Waiting"<<endl;
		pthread_cond_wait(&count_nonzero, &count_lock);
	  }
	  count = count - 1;
	  cout<<"@@@@@@@@@@@@"<<count<<endl;
	  pthread_mutex_unlock(&count_lock);
	  return 0;
	}

	static void* increment_count(void* argv) {
	  pthread_mutex_lock(&count_lock);
	  if (count == 0)
	  {
	  	cout<<"Signaling"<<endl;
//		pthread_cond_signal(&count_nonzero);
		pthread_cond_broadcast(&count_nonzero);
	  }
	  count = count + 1;
	  cout<<"############"<<count<<endl;
	  pthread_mutex_unlock(&count_lock);
	  return 0;
	}

	static void R()
	{
		Thread t1(1, &decrement_count);
		t1.Run(0);
		Thread t2(2, &increment_count);
		t2.Run(0);
		Thread t3(3, &increment_count);
		t3.Run(0);
		Thread t4(4, &decrement_count);
		t4.Run(0);
		Thread t5(5, &increment_count);
		t5.Run(0);
		Thread t6(6, &increment_count);
		t6.Run(0);
	}
};

unsigned WS::count = 0;
pthread_mutex_t WS::count_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t WS::count_nonzero = PTHREAD_COND_INITIALIZER;

TEST(MultiThreading, testTWO)
{
	ASSERT_EQ(0,WS::count);
	WS::R();
	sleep(1);
	ASSERT_EQ(2,WS::count);
}
//////////////////////////////////////////////////////////////////////////////////

int main( int argc, char** argv )
{

	/*::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();*/
	if (argc < 3)
	{
		cerr << "usage: ./ThreadPoolServer portNum filename" << endl;
                return -1;
	}

    int Port = atoi ( argv [ 1 ] );
	char* fileName = argv[2];

	ThreadPoolServer tps(Port, fileName);
	tps.Run();

	return 0;
}
