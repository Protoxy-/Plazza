#ifndef   NAMEDPIPE_HH_
#define   NAMEDPIPE_HH_

#include <unistd.h>
#include <iostream>
#include <fstream>

#include "System.hh"

class             NamedPipe
{
  int             _id;
  int             _action;
  std::string     com_name;
  std::string     log_name;
  std::ofstream   fd_com_in;
  std::ifstream   fd_com_out;
  std::ofstream   fd_log_in;
  std::ifstream   fd_log_out;
  std::list<std::string> coms_in;
  std::list<std::string> coms_out;
  std::list<std::string> logs_in;
  std::list<std::string> logs_out;


public:
  NamedPipe(int, int);
  ~NamedPipe();
  int               end();
  void              setAction();
  int               getAction() const;
  void              putCommand(const std::string);
  std::list<std::string> *getCommand();
  void              putLog(const std::string);
  std::list<std::string> *getLog();
};

#endif
