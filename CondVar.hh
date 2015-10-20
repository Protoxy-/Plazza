#ifndef CONDVAR_HH_
#define CONDVAR_HH_

#include <pthread.h>

#include "Exception.hh"

class   CondVar
{
  pthread_cond_t      _cond;
  pthread_mutex_t     _mutex;
public:
  CondVar();
  ~CondVar();
  void            freeaze();
	void            unfreaze_one();
	void            unfreeze_all();
};

#endif
