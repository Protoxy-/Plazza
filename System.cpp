#include "System.hh"

Param::Param(float mul, int max, int res)
{
  _mulTime = mul;
  _maxCook = max;
  _resTime = res;
}

Param::~Param()
{

}

float     Param::getMulTime() const
{
  return (_mulTime);
}

int       Param::getMaxCook() const
{
  return (_maxCook);
}

int       Param::getResTime() const
{
  return (_resTime);
}


CookParam::CookParam(Param *param, int id, std::list<Ingredient> *ingrs, Mutex *mutex)
{
  _param = param;
  _id = id;
  _ingrs = ingrs;
  _mutex = mutex;
}

CookParam::CookParam(const CookParam *cookPar)
{
  _param = cookPar->getParam();
  _id = cookPar->getId();
  _ingrs = cookPar->getIngrs();
  _mutex = cookPar->getMutex();
}

CookParam::~CookParam()
{

}

Param                 *CookParam::getParam() const
{
  return (_param);
}

std::list<Ingredient> *CookParam::getIngrs() const
{
  return (_ingrs);
}

int                   CookParam::getId() const
{
  return (_id);
}

Mutex                 *CookParam::getMutex() const
{
  return (_mutex);
}
