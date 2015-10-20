#include "Pizza.hh"
#include "Factory.hh"

TypePizza Pizza::getType() const
{
  return _type;
}

TaillePizza Pizza::getSize() const
{
  return _size;
}

std::string const Pizza::getTypeStr() const
{
  switch (_type)
  {
    case 1:
      return ("Regina");
      break;
    case 2:
      return ("Margarita");
      break;
    case 4:
      return ("Americaine");
      break;
    default:
      return ("Fantasia");
      break;
  }
}

std::string const Pizza::getSizeStr() const
{
  switch (_type)
  {
    case 1:
      return ("S");
      break;
    case 2:
      return ("M");
      break;
    case 4:
      return ("L");
      break;
    case 8:
      return ("XL");
      break;
    default:
      return ("XXL");
      break;
  }
}

const std::string Pizza::pack() const
{
  std::stringstream	to_return;

  to_return << _type << " " << _size << std::endl;
  return (to_return.str());
}

Pizza  *Pizza::unpack(const std::string &data_string) const
{
  TypePizza	type;
  TaillePizza	size;
  std::string	data(data_string);
  PizzaFactory	fact;

  type = static_cast<TypePizza>(atoi(data.substr(0, data.find(" ")).c_str()));
  data.erase(0, data.find(" "));
  size = static_cast<TaillePizza>(atoi(data.c_str()));
  return fact.selectType(type, size);
}

Pizza::~Pizza()
{
}
