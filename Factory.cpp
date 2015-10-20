#include "Factory.hh"

void	PizzaFactory::init_maps()
{
  _pizzaType["regina"] = Regina;
  _pizzaType["margarita"] = Margarita;
  _pizzaType["americaine"] = Americaine;
  _pizzaType["fantasia"] = Fantasia;
  _pizzaSize["s"] = S;
  _pizzaSize["m"] = M;
  _pizzaSize["l"] = L;
  _pizzaSize["xl"] = XL;
  _pizzaSize["xxl"] = XXL;
}

Pizza	*PizzaFactory::selectType(TypePizza type, TaillePizza size) const
{
  switch (type)
    {
    case (Regina):
      return (new PizzaRegina(type, size));
    case (Margarita):
      return (new PizzaMargarita(type, size));
    case (Americaine):
      return (new PizzaAmericaine(type, size));
    case (Fantasia):
      return (new PizzaFantasia(type, size));
    }
}

std::list<Pizza *> PizzaFactory::createPizza(const std::string &order)
{
  TypePizza	type;
  TaillePizza	size;
  std::list<Pizza *> pizza_orders;
  std::string	single_order;
  std::string	orders(order);
  std::map<std::string, TypePizza>::iterator type_buffer;
  std::map<std::string, TaillePizza>::iterator size_buffer;
  int	number_pizza;

  init_maps();
  while (orders.size())
    {
      if (orders.find(";") == std::string::npos)
	{
	  single_order = orders;
	  orders = "";
	}
      else
	{
	  single_order = orders.substr(0, orders.find(";", 0));
	  orders.erase(0, orders.find(";", 0) + 2);
	}
      std::transform(single_order.begin(), single_order.end(), single_order.begin(),
		     ::tolower);
      if (std::count(single_order.begin(), single_order.end(), ' ') > 3)
	throw errExcept("Too much argument");
      type_buffer = _pizzaType.find(single_order.substr(0, single_order.find(" ")));
      if (type_buffer == _pizzaType.end())
	throw errExcept(single_order.substr(0, single_order.find(" "))
			 + std::string(" : Unknown pizza type"));
      type = type_buffer->second;
      single_order.erase(0, single_order.find(" ") + 1);
      size_buffer = _pizzaSize.find(single_order.substr(0, single_order.find(" ")));
      if (size_buffer == _pizzaSize.end())
	throw errExcept(single_order.substr(0, single_order.find(" "))
			 + std::string(" : Unknown pizza size"));
      size = size_buffer->second;
      single_order.erase(0, single_order.find(" ") + 2);
      if (single_order.find(" ") < single_order.find(";"))
	number_pizza = atoi(single_order.substr(0, single_order.find(" ")).c_str());
      else
	number_pizza = atoi(single_order.substr(0, single_order.find(";")).c_str());
      for (int i = 0; i < number_pizza; i++)
	pizza_orders.push_front(selectType(type, size));
    }
  return (pizza_orders);
}
