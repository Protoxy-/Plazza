#ifndef INPUT_HH_
#define INPUT_HH_

#include <string>
#include <iostream>
#include <sstream>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "System.hh"

class           Input
{
  int           mousePos[2];
  int           click;
  int           textReady;
  int           end;
  int           sel;
  std::string   str;
  std::string   tmpStr;
  SDL_Event     event;

public:
  Input();
  ~Input();

  void         getNextParam(SDLKey);
  void         handleText();
  void         handle();
  std::string  getString() const;
  void         reset();
  int          getReady() const;
  int          *getMousePos();
  int          getMouseClick() const;
  void         resetMouseClick();
  int          getEnd() const;
};

#endif
