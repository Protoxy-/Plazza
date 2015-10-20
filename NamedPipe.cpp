#include "NamedPipe.hh"

NamedPipe::NamedPipe(int id, int way)
{
  std::stringstream       tmp;

  _id = id;
  _action = 0;
  tmp << "FIFOS/PROC_" << id << "_INPUT";
  com_name = tmp.str();
  tmp.str("");
  tmp << "FIFOS/PROC_" << id << "_OUTPUT";
  log_name = tmp.str();
  if (way == 0)
  {
    fd_com_in.open(com_name.c_str());
    if (!fd_com_in.is_open())
      throw errAbort("open fifo output on reception fail");
  }
  if (way == 1)
  {
    fd_com_out.open(com_name.c_str());
    if (!fd_com_out.is_open())
      throw errAbort("open fifo input on kitchen fail");
  }
}

NamedPipe::~NamedPipe()
{
  fd_com_in.close();
  fd_log_out.close();
  fd_log_in.close();
  fd_com_out.close();
}

int                       NamedPipe::end()
{
  std::list<std::string>::iterator it;
  int                              i;

  i = 0;
  if (coms_out.size() != 0)
  for (it = coms_out.begin(); it != coms_out.end(); it++)
  {
    if ((*it) == "!")
      return (1);
    i++;
  }
  return (0);
}

void                      NamedPipe::setAction()
{
  _action++;
  if (_action == 2)
    _action = 0;
}

int                       NamedPipe::getAction() const
{
  return (_action);
}

void                      NamedPipe::putCommand(const std::string msg)
{
  coms_in.push_front(msg);
  while (_action == 0 && logs_in.size() != 0)
  {
    fd_com_in << (*coms_in.begin()) << std::endl;
    coms_in.pop_front();
  }
}

std::list<std::string> *NamedPipe::getCommand()
{
  std::string          line;


  while (_action == 0 && getline(fd_com_out, line) > 0)
  {
    coms_out.push_front(line);
  }
  return (&coms_out);
}

void                      NamedPipe::putLog(const std::string msg)
{
  logs_in.push_front(msg);
  while (_action == 1 && logs_in.size() != 0)
  {
    fd_log_in << (*logs_in.begin()) << std::endl;
    logs_in.pop_front();
  }
}

std::list<std::string> *NamedPipe::getLog()
{
  std::string          line;

  while (_action == 1 && getline(fd_com_out, line) > 0)
  {
    coms_out.push_front(line);
  }
  return (&coms_out);
}
