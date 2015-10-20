#ifndef  KITCHENDATA_HH_
#define  KITCHENDATA_HH_

#include "Pizza.hh"
#include "System.hh"
#include "NamedPipe.hh"

class                   KitchenData
{
  std::list<Pizza*>     pizzas;
  std::list<Ingredient> ingrs;
  NamedPipe             *pipe;

public:
  void                  setPizza(std::list<Pizza*>);
  void                  putPizza(Pizza *);
  void                  popPizza();
  std::list<Pizza*>     getPizza() const;
  void                  setIngrs(std::list<Ingredient>);
  std::list<Ingredient> getIngrs() const;
  void                  setPipe(NamedPipe *);
  NamedPipe             *getPipe() const;
};

#endif
