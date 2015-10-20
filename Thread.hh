#ifndef THREADS_HH_
#define THREADS_HH_

#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

#include "Exception.hh"

class Thread
{
  pthread_t   _thread;
public:
  Thread(void *);
  ~Thread();
  void        join();
  pthread_t   get() const;
};

class PipeThread
{
  pthread_t   _thread;
public:
  PipeThread(void *);
  ~PipeThread();
  std::string join();
  pthread_t   get() const;
};

#endif
