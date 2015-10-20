#include "CondVar.hh"

CondVar::~CondVar(void)
{
  pthread_cond_destroy(&_cond);
  pthread_mutex_destroy(&_mutex);
}

void    CondVar::freeaze(void)
{
  pthread_mutex_lock(&_mutex);
  pthread_cond_wait(&_cond, &_mutex);
  pthread_mutex_unlock(&_mutex);
}

void    CondVar::unfreaze_one(void)
{
  pthread_cond_signal(&_cond);
}

void    CondVar::unfreeze_all(void)
{
  pthread_cond_broadcast(&_cond);
}
