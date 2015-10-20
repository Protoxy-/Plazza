#ifndef MENU_HH_
#define MENU_HH_

#include <unistd.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "System.hh"
#include "InputSDL.hh"
#include "KitchenData.hh"

class           Interface
{
  Param         *param;
  std::list<KitchenData*>   kitchensData;
  Input   *input;
  SDL_Color     color_princ;
  SDL_Color     color_entry;
  SDL_Color     color_shadow;
  TTF_Font      *main_font;
  TTF_Font      *mainSh_font;
  TTF_Font      *entry_font;
  TTF_Font      *entrySh_font;
  SDL_Event     event;
  SDL_Surface   *screen;
  SDL_Surface   *back_sprt;
  SDL_Surface   *button_sprt;
  SDL_Surface   *pizza_sprt;
  int           posComList;
  int           posComSize;
  int           posComMenu;
  int           posStatList;
  int           posStatSize;
  int           posStatMenu;
public:
  Interface();
  ~Interface();

  void        initColor();
  void        loadFile();
  Input  *getInput() const;
  void        setSurfaceAlpha(SDL_Surface *, Uint8);
  void        checkKey();
  void        putDataList(std::list<KitchenData*> *kitchensData);
  void        display();
  void        displayInput();
  void        displayKitchenMenu(int);
  void        displayKitchenList(int);
  void        menuControl();
  void        scrollControl();
  void        loop();
  void        start();
};


#endif
