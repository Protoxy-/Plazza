#include "Thread.hh"
#include "Cook.hh"

static void *handleCall(void *object)
{
  Cook *cook = static_cast<Cook *>(object);
  cook->actions();
  pthread_exit(0);
}

Thread::Thread(void *obj)
{
  if (pthread_create(&this->_thread, NULL, &handleCall, obj) != 0)
	  throw errAbort("pthread_create fail");
}

Thread::~Thread(void)
{
}

void    Thread::join()
{
  pthread_join(_thread, NULL);
}

pthread_t    Thread::get() const
{
  return (_thread);
}

static void *PipeHandleCall(void *fd)
{
  std::ifstream *input = static_cast<std::ifstream*>(fd);
  std::string   *line = new std::string;

  getline(*input, *line);
  pthread_exit(0);
  return (static_cast<void *>(line));
}

PipeThread::PipeThread(void *obj)
{
  if (pthread_create(&this->_thread, NULL, &PipeHandleCall, obj) != 0)
    throw errAbort("pthread_create fail");
}

PipeThread::~PipeThread(void)
{
}

std::string     PipeThread::join()
{
  void          **retVal;

  pthread_join(_thread, retVal);
  return (*(static_cast<std::string*>(*retVal)));
}

pthread_t    PipeThread::get() const
{
  return (_thread);
}
