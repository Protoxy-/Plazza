#ifndef MUTEX_HH_
#define MUTEX_HH_

#include <pthread.h>

#include "Exception.hh"

class Mutex
{
    private:
        pthread_mutex_t     mutex_;

        Mutex(Mutex const &mutex);
        Mutex &operator=(Mutex const &mutex);
    public:
        Mutex(void);

        void                lock(void);
        void                unlock(void);
        int trylock();

        ~Mutex(void);
};

class MutexScopeLock
{
    private:
        Mutex &mutex_;

        MutexScopeLock(void);
        MutexScopeLock(MutexScopeLock const &);
        MutexScopeLock &operator=(MutexScopeLock const &);
    public:
        MutexScopeLock(Mutex &mutex);
        ~MutexScopeLock(void);
};


#endif
