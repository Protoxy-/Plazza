#include "Processes.hh"

int Processes::Fork()
{
  return (fork());
}

void Processes::Exit(int status)
{
  exit(status);
}

pid_t Processes::Wait(int *param)
{
  return (wait(param));
}
