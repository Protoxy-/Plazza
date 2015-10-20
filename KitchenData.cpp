#include "KitchenData.hh"

void                  KitchenData::setPizza(std::list<Pizza*> _pizza)
{
  pizzas = _pizza;
}

void                  KitchenData::putPizza(Pizza* _pizza)
{
  pizzas.push_front(_pizza);
}

void                  KitchenData::popPizza()
{
  pizzas.pop_front();
}

std::list<Pizza*>     KitchenData::getPizza() const
{
  return (pizzas);
}

void                  KitchenData::setIngrs(std::list<Ingredient> _ingrs)
{
  ingrs = _ingrs;
}

std::list<Ingredient> KitchenData::getIngrs() const
{
  return (ingrs);
}

void                  KitchenData::setPipe(NamedPipe *_pipe)
{
  pipe = _pipe;
}

NamedPipe             *KitchenData::getPipe() const
{
  return (pipe);
}
