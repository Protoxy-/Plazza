#ifndef FACTORY_HH_
#define FACTORY_HH_

#include <list>
#include <map>
#include <algorithm>
#include <cstdlib>
#include <sstream>
#include "Pizza.hh"
#include "System.hh"
#include "Exception.hh"

#include "PizzaAmericaine.hh"
#include "PizzaRegina.hh"
#include "PizzaMargarita.hh"
#include "PizzaFantasia.hh"

class PizzaFactory
{
  std::map<std::string, TypePizza> _pizzaType;
  std::map<std::string, TaillePizza> _pizzaSize;
  void	init_maps();
public:
  std::list<Pizza *> createPizza(const std::string &);
  Pizza *selectType(TypePizza, TaillePizza) const;
};

#endif
