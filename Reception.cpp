#include "Reception.hh"

#include "NamedPipe.hh"


Reception::Reception(double mulTime, int maxCook, int resTime)
{
  interface = new Interface();
  factory = new PizzaFactory;
  _param = new Param(mulTime, maxCook, resTime);
}

Reception::~Reception()
{
}

int    Reception::kitchenDistribution(std::list<Pizza*> reqPizza)
{
  std::list<KitchenData*>::iterator   kitchenIt;
  int                                 i;

  if (kitchens.size() == 0)
    return (1);
  i = 0;
  for (kitchenIt = kitchensData.begin(); kitchenIt != kitchensData.end(); kitchenIt++)
  {
    while ((*kitchenIt)->getPizza().size() < _param->getMaxCook() * 2)
    {
      (*kitchenIt)->putPizza(reqPizza.front());
      (*kitchenIt)->getPipe()->putCommand(reqPizza.front()->pack());
      reqPizza.pop_front();
      if (reqPizza.size() == 0)
	      return (0);
    }
    (*kitchenIt)->getPipe()->setAction();
    i++;
  }
  return (1);
}

void    Reception::createKitchen()
{
  KitchenData         *tmp = new KitchenData;
  std::stringstream   file_name;

  file_name << "FIFOS/PROC_" << kitchens.size() << "_INPUT";
  mkfifo(file_name.str().c_str(), 0666);
  file_name.str("");
  file_name << "FIFOS/PROC_" << kitchens.size() << "_OUTPUT";
  mkfifo(file_name.str().c_str(), 0666);
  kitchens.push_back(new Kitchen(_param, kitchens.size()));
  tmp->setPipe(new NamedPipe(kitchens.size() - 1, 0));
  kitchensData.push_back(tmp);
}

void    Reception::requestOrder()
{
  std::list<Pizza*>     reqPizza;
  std::string           com;
  int                   chk;
  int                   i;

  com = interface->getInput()->getString();
  try
  {
    reqPizza = factory->createPizza(com);
  }
  catch (errExcept &e)
  {
    std::cout << "Syntax warning: " << e.what() << std::endl;
    interface->getInput()->reset();
    return;
  }
  i = 0;
  while ((chk = kitchenDistribution(reqPizza)) == 1)
  {
    createKitchen();
    i++;
  }
  interface->getInput()->reset();
}

void    Reception::manageOutLogs()
{
  std::list<Pizza*>                   outPizza;
  std::list<Pizza*>::iterator         pizzaIt;
  std::list<KitchenData*>::iterator   kitchenIt;
  std::list<std::string>::iterator    strIt;
  PizzaRegina                         _pizzaChk(Regina, XL);
  Pizza                               *pizzaTmp;
  std::string                         out;
  int                                 i;


  i = 0;
  for (kitchenIt = kitchensData.begin(); kitchenIt != kitchensData.end(); kitchenIt++)
  {
    for (strIt = (*kitchenIt)->getPipe()->getLog()->begin(); strIt != (*kitchenIt)->getPipe()->getLog()->end(); strIt++)
    {
      out = (*strIt);
    if (out == "")
      strIt++;
    pizzaTmp = _pizzaChk.unpack(out);
    outPizza = (*kitchenIt)->getPizza();
    for (pizzaIt = outPizza.begin(); pizzaIt != outPizza.end(); pizzaIt++)
    {
      if ((*pizzaIt)->getType() == pizzaTmp->getType() && (*pizzaIt)->getSize() == pizzaTmp->getSize())
      {
	       outPizza.remove((*pizzaIt));
	       (*kitchenIt)->setPizza(outPizza);
	       break;
      }
    }
    }
    (*kitchenIt)->getPipe()->setAction();
    i++;
  }
}

void    Reception::loop()
{
  std::list<KitchenData*>::iterator   kitchenIt;

  while (42)
  {
    interface->loop();
    if (interface->getInput()->getReady() == 1)
      requestOrder();
    if (kitchensData.size() != 0)
    for (kitchenIt = kitchensData.begin(); kitchenIt != kitchensData.end(); kitchenIt++)
    {
      (*kitchenIt)->getPipe()->putCommand("");
    }
    usleep(REFRESH);


    interface->putDataList(&kitchensData);
    if (interface->getInput()->getEnd() != 0)
    {
      quit();
      break;
    }
    usleep(REFRESH);
  }
}

void    Reception::manage()
{
  loop();
}

void    Reception::quit()
{


}
