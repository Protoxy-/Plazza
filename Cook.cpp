#include "Cook.hh"

Cook::Cook(Param *param, int id, std::list<Ingredient> *Ingredients, Mutex *ingrM, NamedPipe *pipe, Mutex *pipeM):
  _id(id), _param(param), _pipeMutex(pipeM), _ingredients(Ingredients), _ingrMutex(ingrM), _work(0)
{
  _thread = new Thread(static_cast<void *>(this));
  _currentPizza = NULL;
}

Cook::~Cook()
{

}

int	Cook::getWork() const { return (_work);}
void	Cook::setPizza(Pizza *pizza) { _currentPizza = pizza;}
void	Cook::setWork(int work) { _work = work;}

time_t      Cook::getTime()
{
  struct timeval curTime;
  int milli;

  gettimeofday(&curTime, NULL);
  milli = curTime.tv_usec / 1000;

  return static_cast<time_t>(milli);
}


void      Cook::actions()
{
  float   time;

  while (42)
  {

    if (_work == 1 && _time == 0)
      {
	       _time = getTime();
      }
    else if (_work == 1)
      {
	switch (_currentPizza->getType())
	  {
	  case (Regina):
	    time = 1;
	    break;
	  case (Margarita):
	    time = 2;
	    break;
	  case (Americaine):
	    time = 2;
	    break;
	  case (Fantasia):
	    time = 4;
	    break;
	  }
	time *= _param->getMulTime();
	if (_time >= time)
	  {
	    delete(_currentPizza);
	    _work = 0;
	    _time = 0;
	  }
      }
    usleep(REFRESH);
  }
}

static void	setupRemoveList(std::list<Ingredient> &to_rm, TypePizza pizza_type)
{
  switch (pizza_type)
    {
    case (Regina):
      to_rm.push_back(Doe);
      to_rm.push_back(Tomato);
      to_rm.push_back(Gruyere);
      break;
    case (Margarita):
      to_rm.push_back(Doe);
      to_rm.push_back(Tomato);
      to_rm.push_back(Gruyere);
      to_rm.push_back(Ham);
      to_rm.push_back(Mushrooms);
      break;
    case (Americaine):
      to_rm.push_back(Doe);
      to_rm.push_back(Tomato);
      to_rm.push_back(Gruyere);
      to_rm.push_back(Steak);
      break;
    case (Fantasia):
      to_rm.push_back(Doe);
      to_rm.push_back(Tomato);
      to_rm.push_back(Eggplant);
      to_rm.push_back(GoatCheese);
      to_rm.push_back(ChiefLove);
      break;
    }
}

void Cook::removeIngredients(TypePizza pizza_type)
{
  std::list<Ingredient>::iterator it_rm;
  std::list<Ingredient>::iterator it_list;
  std::list<Ingredient>		  to_rm;

  if(_ingrMutex->trylock() == 0)
    {
      setupRemoveList(to_rm, pizza_type);
      for (it_list = to_rm.begin(); it_list != to_rm.end(); it_list++)
	{
	  it_rm = std::find(_ingredients->begin(), _ingredients->end(), *it_list);
	  if(it_rm != _ingredients->end())
	    _ingredients->erase(it_rm);
	}
    _ingrMutex->unlock();
    }
}
