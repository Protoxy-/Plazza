#ifndef RECEPTION_HH_
#define RECEPTION_HH_

#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <list>

#include "System.hh"
#include "InterfaceSDL.hh"
#include "Kitchen.hh"
#include "Factory.hh"

#include "Pizza.hh"

class   Reception
{
  Param                    *_param;
  Interface                *interface;
  PizzaFactory             *factory;
  std::list<Kitchen*>      kitchens;
  std::list<KitchenData*>  kitchensData;

public:
  Reception(double, int, int);
  ~Reception();
  int  kitchenDistribution(std::list<Pizza*>);
  void createKitchen();
  void requestOrder();
  void manageOutLogs();
  void manage();
  void loop();
  void quit();
};

#endif
