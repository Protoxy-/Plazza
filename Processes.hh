#ifndef PROCESSES_HH_
#define PROCESSES_HH_

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstdlib>

#include "Exception.hh"

class   Processes
{
public:
  int Fork();
  void Exit(int);
  pid_t Wait(int *);
};

#endif
