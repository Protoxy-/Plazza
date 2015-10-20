#ifndef PIZZA_HH_
#define PIZZA_HH_

#include <string>
#include <sstream>
#include <iostream>

#include "System.hh"

class           Pizza
{
protected:
  TypePizza   _type;
  TaillePizza   _size;

public:
  virtual ~Pizza() = 0;
  TypePizza getType() const;
  std::string const getTypeStr() const;

  TaillePizza getSize() const;
  std::string const getSizeStr() const;

  const std::string pack() const;
  Pizza *unpack(const std::string &) const;
};

#endif
