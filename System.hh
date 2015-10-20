#ifndef SYSTEM_HH_
#define SYSTEM_HH_

#include <iostream>
#include <sstream>
#include <list>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "Exception.hh"
#include "CondVar.hh"
#include "Thread.hh"
#include "Mutex.hh"
#include "Processes.hh"

#define  REFRESH 500

enum Ingredient
{
  Doe = 0,
  Tomato = 1,
  Gruyere = 2,
  Ham = 3,
  Mushrooms = 4,
  Steak = 5,
  Eggplant = 6,
  GoatCheese = 7,
  ChiefLove = 8
};

enum    TypePizza
{
  Regina = 1,
  Margarita = 2,
  Americaine = 4,
  Fantasia = 8
};

enum     TaillePizza
{
  S = 1,
  M = 2,
  L = 4,
  XL = 8,
  XXL = 16,
};

class             Param
{
  float           _mulTime;
  int             _maxCook;
  int             _resTime;
public:
  Param(float, int, int);
  ~Param();
  float     getMulTime() const;
  int       getMaxCook() const;
  int       getResTime() const;
};

class             CookParam
{
  Param                  *_param;
  int                   _id;
  std::list<Ingredient> *_ingrs;
  Mutex                 *_mutex;
public:
  CookParam(Param *, int, std::list<Ingredient> *, Mutex *);
  CookParam(const CookParam *param);
  ~CookParam();

  Param                 *getParam() const;
  std::list<Ingredient> *getIngrs() const;
  int                   getId() const;
  Mutex                 *getMutex() const;
};

#endif
