#include <string>
#include <iostream>
#include <sstream>
#include <stdlib.h>

#include "Exception.hh"
#include "Reception.hh"

#include "Factory.hh"

int   main(int av, char **ac)
{
  if (av != 4)
  {
    std::cout << "Usage: ./plazza <Multipler> <Cookers> <Time>" << std::endl;
    return (-1);
  }
  try
  {
    Reception *resto = new Reception(atof(ac[1]), atoi(ac[2]), atoi(ac[3]));
    resto->manage();
    delete resto;
  }
  catch (errAbort &e)
  {
    std::cout << "Error: " << e.what() << std::endl;
    return (-1);
  }
  catch (errGraphic &e)
  {
    std::cout << "SDL Error: " << e.what() << std::endl;
    return (-1);
  }
  std::cout << "See you soon !" << std::endl;
  return (0);
}
