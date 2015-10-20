#ifndef KITCHEN_HH_
#define KITCHEN_HH_

#include <string>
#include <iostream>
#include <list>
#include <sys/time.h>

#include "System.hh"
#include "Factory.hh"
#include "NamedPipe.hh"
#include "Pizza.hh"
#include "Cook.hh"

class                   Kitchen : public Processes
{
  int                   _id;
  Param                 *_param;
  PizzaFactory          *_factory;
  std::list<Cook*>      cooks;
  std::list<Pizza*>     pizzas;
  std::list<Ingredient> *ingredients;
  NamedPipe             *_pipes;
  Mutex                 *_ingrMutex;
  Mutex                 *_pipeMutex;
  time_t                _time;
  int                   _pid;

public:
  Kitchen(Param *, int);
  ~Kitchen();

  void  initObjs();
  int   update();
  void  cookDistribution();
  void  loop();
  void  restore();
};

#endif
