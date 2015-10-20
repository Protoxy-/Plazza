#ifndef COOK_HH_
#define COOK_HH_

#include <algorithm>
#include <sys/time.h>
#include <unistd.h>
#include "System.hh"
#include "NamedPipe.hh"
#include "Pizza.hh"

class Cook
{
private:
  int                   _id;
  Param                 *_param;
  NamedPipe             *_pipes;
  Mutex                 *_pipeMutex;
  std::list<Ingredient> *_ingredients;
  Mutex                 *_ingrMutex;
  Thread                *_thread;
  Pizza                 *_currentPizza;
  int                   _work;
  time_t                _time;

public:
  Cook(Param *, int, std::list<Ingredient> *, Mutex *, NamedPipe *, Mutex *);
  ~Cook();
  time_t  getTime();
  void    actions();
  int	  getWork() const;
  void	  setPizza(Pizza *);
  void	  setWork(int);
  void    removeIngredients(TypePizza);
};

#endif
