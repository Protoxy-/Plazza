#ifndef PIZZAAMERICAINE_HH_
#define PIZZAAMERICAINE_HH_

#include "Pizza.hh"

class  PizzaAmericaine : public Pizza
{
public:
  PizzaAmericaine(TypePizza, TaillePizza);
  ~PizzaAmericaine();
};

#endif
