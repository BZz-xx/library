#include "Mutex.h"

Mutex::Mutex()
{
    pthread_mutex_init( &mutex, NULL );
}

Mutex::~Mutex()
{
    int err = pthread_mutex_destroy( &mutex );
    if (err < 0)
		perror("error in Mutex Destructor");
}

MutexType Mutex::GetMutex()
{
	return mutex;
}

bool Mutex::TryLock()
{
    return !pthread_mutex_trylock( &mutex ) ;
}

void Mutex::Lock()
{
	int err = pthread_mutex_lock( &mutex );
	if (err < 0)
		perror("error Mutex Lock");
}

void Mutex::Unlock()
{
    int err = pthread_mutex_unlock( &mutex );
    if (err < 0)
		perror("error Mutex Unlock");
}
