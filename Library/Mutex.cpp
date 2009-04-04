#include "Mutex.h"

Mutex::Mutex()
{
    pthread_mutex_init ( &mutex, NULL );
}

Mutex::~Mutex()
{
    pthread_mutex_destroy( &mutex );
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
	pthread_mutex_lock( &mutex );
}

void Mutex::Unlock()
{
    pthread_mutex_unlock( &mutex );
}
