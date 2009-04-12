#ifndef MUTEX_H
#define MUTEX_H

#include <stdlib.h>
#include <iostream>
#include <pthread.h>

typedef pthread_mutex_t MutexType;

class Mutex {
//FIELDS
    MutexType mutex;
//METHODS
    public:
        Mutex();
        ~Mutex();

    public:
		MutexType GetMutex();
        void Lock();
        void Unlock();
        bool TryLock();

    private:
//        Mutex( const Mutex& );
//        void operator = ( const Mutex& );
};

#endif // MUTEX_H
