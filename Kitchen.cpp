#include "Kitchen.hh"

Kitchen::Kitchen(Param *param, int id)
{
  if (Fork() == 0)
  {
    _factory = new PizzaFactory;
    _pipes = new NamedPipe(id, 1);
    ingredients = new std::list<Ingredient>;
    _ingrMutex = new Mutex;
    _pipeMutex = new Mutex;
    _param = param;
    _id = id;
    _time = time(NULL);
    try
    {
      initObjs();
      loop();
    }
    catch (errAbort &e)
    {
      std::cout << "Err: " << e.what() << std::endl;
      Exit(EXIT_FAILURE);
    }
  }
}

Kitchen::~Kitchen()
{
  delete ingredients;
  delete _pipeMutex;
  delete _ingrMutex;
}

void  Kitchen::initObjs()
{
  int   i;
  int   j;

  for (i = 0; i < 9; i++)
  {
    for (j = 0; j < 5; j++)
    {
      ingredients->push_back((Ingredient)i);
    }
  }
  for (i = 0; i < _param->getMaxCook(); i++)
  {
    cooks.push_back(new Cook(_param, _id, ingredients, _ingrMutex, _pipes, _pipeMutex));
  }
}

int  Kitchen::update()
{
  PizzaRegina    _pizzaTmp(Regina, XL);
  std::string    _lastEntry;
  std::list<Cook *>::iterator it;
  std::list<std::string>::iterator strIt;

  if (_pipeMutex->trylock() == 0)
  {
  for (strIt = _pipes->getCommand()->begin(); strIt != _pipes->getCommand()->end(); strIt++)
  {
    _lastEntry = (*strIt);
    if (_lastEntry.c_str()[0]  == '!')
      return (1);
    if (!_lastEntry.empty())
    {
      std::cout << "get pizza : " << _lastEntry << std::endl;
      pizzas.push_front(_pizzaTmp.unpack(_lastEntry));
    }
  }
  _pipeMutex->unlock();
  }
  return (0);
}

void  Kitchen::cookDistribution()
{
  std::list<Cook *>::iterator it;

  if (pizzas.size())
  for (it = cooks.begin(); it != cooks.end() && pizzas.size(); it++)
  {
    if ((*it)->getWork() == 0)
    {
        _time = time(NULL);
        (*it)->setPizza(pizzas.front());
        pizzas.pop_front();
        (*it)->setWork(1);
      }
    }
}

void  Kitchen::loop()
{
  while (42)
  {
    if (update() == 1)
    {
      Exit(EXIT_SUCCESS);
    }
    cookDistribution();
    _pipes->setAction();
    usleep(REFRESH);
    _pipes->setAction();
    restore();
    usleep(REFRESH);
  }
}

void  Kitchen::restore()
{
  time_t         curTime;
  struct timeval tv;  
  int    i;

  curTime = time(NULL);

  if (gettimeofday(&tv, 0x0) == -1)
    throw errAbort("gettimeofday() fail");
  if (((((int)difftime(curTime, _time) * 1000000  + tv.tv_usec) / 1000) % _param->getResTime()) == 0)
  {
    for (i = 0; i < 9; i++)
    {
      if (_ingrMutex->trylock() == 0)
      {
        ingredients->push_back((Ingredient)i);
        _ingrMutex->unlock();
      }
    }
  }
}
