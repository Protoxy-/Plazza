#include "Mutex.hh"

Mutex::Mutex(void)
{
    pthread_mutex_init(&this->mutex_, NULL);
}

Mutex::~Mutex(void)
{
    pthread_mutex_destroy(&this->mutex_);
}

Mutex::Mutex(Mutex const &)
{
}

Mutex &Mutex::operator=(Mutex const &)
{
    return (*this);
}

void Mutex::lock(void)
{
    pthread_mutex_lock(&this->mutex_);
}

void Mutex::unlock(void)
{
    pthread_mutex_unlock(&this->mutex_);
}

int Mutex::trylock()
{
  return pthread_mutex_trylock(&this->mutex_);
}

MutexScopeLock::MutexScopeLock(void)
    : mutex_(* new Mutex())
{
}

MutexScopeLock::MutexScopeLock(MutexScopeLock const &)
    : mutex_(* new Mutex())
{
}

MutexScopeLock &MutexScopeLock::operator=(MutexScopeLock const &)
{
    return (*this);
}

MutexScopeLock::MutexScopeLock(Mutex &mutex)
: mutex_(mutex)
{
    mutex.lock();
}
