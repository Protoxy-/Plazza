#include "InterfaceSDL.hh"

Interface::Interface()
{
  if((SDL_Init(SDL_INIT_EVERYTHING) == -1))
    throw errGraphic("Init");
  screen = SDL_SetVideoMode(1600, 1000, 32, SDL_SWSURFACE);
  if (screen == NULL)
    throw errGraphic("Can't init the window");
  SDL_WM_SetCaption("Plazza", NULL);
  if (TTF_Init() == -1)
    throw errGraphic("Can't init TTF");
  initColor();
  loadFile();
  input = new Input();
  posStatMenu = 0;
  posStatList = 0;
  posStatSize = 0;
  posComMenu = 0;
  posComList = 0;
  posComSize = 0;
}

Interface::~Interface()
{
  TTF_CloseFont(main_font);
  TTF_CloseFont(entry_font);
  TTF_Quit();
  SDL_Quit();
}

void           Interface::initColor()
{
  color_princ.r = 255;
  color_princ.g = 255;
  color_princ.b = 255;

  color_entry.r = 64;
  color_entry.g = 255;
  color_entry.b = 64;

  color_shadow.r = 0;
  color_shadow.g = 0;
  color_shadow.b = 0;
}

void           Interface::loadFile()
{
  if ((main_font = TTF_OpenFont("Data/MainFont.ttf", 40)) == NULL)
    throw errGraphic("Can't load font: MainFont.ttf");
  if ((mainSh_font = TTF_OpenFont("Data/MainFont.ttf", 43)) == NULL)
    throw errGraphic("Can't load font: MainFont.ttf");
  if ((entry_font = TTF_OpenFont("Data/EntryFont.ttf", 60)) == NULL)
    throw errGraphic("Can't load font: EntryFont.ttf");
  if ((entrySh_font = TTF_OpenFont("Data/EntryFont.ttf", 64)) == NULL)
    throw errGraphic("Can't load font: EntryFont.ttf");

  if ((back_sprt = IMG_Load("Data/Background.png")) == NULL)
    throw errGraphic("Can't load img: Background.png");
  if ((button_sprt = IMG_Load("Data/Button.png")) == NULL)
    throw errGraphic("Can't load img: Button.png");
  if ((pizza_sprt = IMG_Load("Data/PizzaTypes.png")) == NULL)
    throw errGraphic("Can't load img: PizzaTypes.png");
}

Input          *Interface::getInput() const
{
  return (input);
}


void                Interface::putDataList(std::list<KitchenData*> *_kitchensData)
{
  kitchensData = *_kitchensData;
}

void               Interface::setSurfaceAlpha(SDL_Surface *surface, Uint8 alpha)
{
  SDL_PixelFormat* fmt = surface->format;

  if(fmt->Amask == 0)
  {
    SDL_SetAlpha( surface, SDL_SRCALPHA, alpha );
  }
  else
  {
    unsigned bpp = fmt->BytesPerPixel;
    float scale = alpha / 255.0f;

    SDL_LockSurface(surface);

    for (int y = 0; y < surface->h; ++y)
    {
      for (int x = 0; x < surface->w; ++x)
      {
        Uint32* pixel_ptr = (Uint32 *)(
        (Uint8 *)surface->pixels
        + y * surface->pitch
        + x * bpp);
        Uint8 r, g, b, a;
        SDL_GetRGBA( *pixel_ptr, fmt, &r, &g, &b, &a );
        *pixel_ptr = SDL_MapRGBA( fmt, r, g, b, scale * a );
      }
    }
    SDL_UnlockSurface(surface);
  }
}

void  Interface::displayInput()
{
  SDL_Surface   *text;
  SDL_Rect      winPos;
  std::stringstream num;
  std::string   entry;

  entry = input->getString();
  if (entry.length() != 0)
  {
    text = TTF_RenderText_Blended(entrySh_font, entry.substr(0, (entry.length() <= 32 ? entry.length() : 32)).c_str(), color_shadow);
    winPos.x = screen->w / 2 - text->w / 2;
    winPos.y = screen->h - (entry.length() <= 32 ? 142 : 197);
    setSurfaceAlpha(text, 128);
    if (SDL_BlitSurface(text, NULL, screen, &winPos) < 0)
      throw errGraphic ("Blit Surface");
    text = TTF_RenderText_Blended(entry_font, entry.substr(0, (entry.length() <= 32 ? entry.length() : 32)).c_str(), color_entry);
    winPos.x = screen->w / 2 - text->w / 2;
    winPos.y = screen->h - (entry.length() <= 32 ? 140 : 190);
    setSurfaceAlpha(text, 255);
    if (SDL_BlitSurface(text, NULL, screen, &winPos) < 0)
      throw errGraphic ("Blit Surface");
  }
  if (entry.length() != 0 && entry.length() > 32)
  {
    text = TTF_RenderText_Blended(entrySh_font, entry.substr(32).c_str(), color_shadow);
    winPos.x = screen->w / 2 - text->w / 2;
    winPos.y = screen->h - 110 + 5;
    setSurfaceAlpha(text, 128);
    if (SDL_BlitSurface(text, NULL, screen, &winPos) < 0)
      throw errGraphic ("Blit Surface");
    text = TTF_RenderText_Blended(entry_font, entry.substr(32).c_str(), color_entry);
    winPos.x = screen->w / 2 - text->w / 2;
    winPos.y = screen->h - 110;
    setSurfaceAlpha(text, 255);
    if (SDL_BlitSurface(text, NULL, screen, &winPos) < 0)
      throw errGraphic ("Blit Surface");
  }
}


void        Interface::displayKitchenMenu(int type)
{
  std::stringstream      str;
  SDL_Surface     *text;
  SDL_Rect        winPos;

  str << "Kit: " << (type == 0 ? posComMenu : posStatMenu) << " Nb: " << (type == 0 ? posComSize : posStatSize);
  text = TTF_RenderText_Blended(main_font, str.str().c_str(), color_princ);
  winPos.x = (type == 0 ? 82 : 1168) + 16;
  winPos.y = 24 + 28 - text->h / 2;
  setSurfaceAlpha(text, 255);
  if (SDL_BlitSurface(text, NULL, screen, &winPos) < 0)
    throw errGraphic ("Blit Surface");
}

void        Interface::displayKitchenList(int type)
{
  std::list<KitchenData*>::iterator kitIt;
  std::list<Pizza*>::iterator pizIt;
  std::list<Pizza*> pizList;
  std::string      str;
  SDL_Surface   *text;
  SDL_Surface   *textTmp;
  SDL_Rect      imgPos;
  SDL_Rect      winPos;
  int           xVec;
  int           pos;
  int           size;
  int           i;

  xVec = (type == 0 ? 0 : 734);
  i = 0;
  for (kitIt = kitchensData.begin(); kitIt != kitchensData.end(); kitIt++)
  {
    if (i ==  (type == 0 ? posComMenu : posStatMenu))
      break;
    i++;
  }
  pizList = (*kitIt)->getPizza();
  if (type == 0)
  {
    posComSize = pizList.size();
    size = posComSize;
    pos = posComList;
  }
  else
  {
    posStatSize = pizList.size();
    size = posStatSize;
    pos = posStatList;
  }
  i = 0;
  if (size != 0)
  for (pizIt = pizList.begin(); pizIt != pizList.end(); pizIt++)
  {
    if (i >= pos && i - pos < 10)
    {
      winPos.x = 82 + xVec;
      winPos.y = 82 + 70 * (i - pos);
      switch ((*pizIt)->getType())
      {
        case 1:
          imgPos.x = 0;
          break;
        case 2:
          imgPos.x = 70;
          break;
        case 4:
          imgPos.x = 70 * 2;
          break;
        default:
          imgPos.x = 70 * 3;
          break;
      }
      imgPos.y = 0;
      imgPos.w = 70;
      imgPos.h = 70;
      if (SDL_BlitSurface(pizza_sprt, &imgPos, screen, &winPos) < 0)
        throw errGraphic ("Blit Surface");
      str = (*pizIt)->getTypeStr() + " " + (*pizIt)->getSizeStr();
      textTmp = TTF_RenderText_Blended(main_font, str.c_str(), color_princ);
      text = TTF_RenderText_Blended(mainSh_font, str.c_str(), color_shadow);
      winPos.x = 82 + 82 + (type == 0 ? -10 : 0) + xVec;
      if (i - pos < 5)
        winPos.y = 82 + 70 * (i - pos) + 35 - text->h / 2 - 5;
      else
        winPos.y = 82 + 70 * (i - pos) + 35 - text->h / 2 + 5;
      setSurfaceAlpha(text, 128);
      if (SDL_BlitSurface(text, NULL, screen, &winPos) < 0)
        throw errGraphic ("Blit Surface");
      text = TTF_RenderText_Blended(main_font, str.c_str(), color_princ);
      winPos.x = 82 + 82 + xVec;
      winPos.y = 82 + 70 * (i - pos) + 35 - text->h / 2;
      setSurfaceAlpha(text, 255);
      if (SDL_BlitSurface(text, NULL, screen, &winPos) < 0)
        throw errGraphic ("Blit Surface");
    }
    i++;
  }
}

void        Interface::menuControl()
{
  SDL_Rect      imgPos;

  imgPos.x = 177;
  imgPos.y = 0;
  imgPos.w = 54;
  imgPos.h = 54;
  if (input->getMouseClick() == 1)
  {
    if (posComMenu != 0)
      if (input->getMousePos()[0] > 0 && input->getMousePos()[0] < 82 && input->getMousePos()[1] > 0 && input->getMousePos()[1] < 82)
        posComMenu--;
    if (posComMenu != kitchensData.size() - 1)
      if (input->getMousePos()[0] > 432 && input->getMousePos()[0] < 612 && input->getMousePos()[1] > 0 && input->getMousePos()[1] < 82)
        posComMenu++;
  }
  if (input->getMouseClick() == 1)
  {
    if (posStatMenu != 0)
      if (input->getMousePos()[0] > 988 && input->getMousePos()[0] < 1170 && input->getMousePos()[1] > 0 && input->getMousePos()[1] < 82)
        posStatMenu--;
    if (posStatMenu != kitchensData.size() - 1)
      if (input->getMousePos()[0] > screen->w - 82 && input->getMousePos()[0] < screen->w && input->getMousePos()[1] > 0 && input->getMousePos()[1] < 82)
        posStatMenu++;
  }
}

void        Interface::scrollControl()
{
  SDL_Rect      imgPos;
  SDL_Rect      winPos;

  imgPos.x = 232;
  imgPos.y = 0;
  imgPos.w = 54;
  imgPos.h = 54;

  winPos.x = 28;
  if (posComSize < 10)
    winPos.y = 414;
  else
  {
    if (input->getMouseClick() == 1)
      if (input->getMousePos()[0] > 24 && input->getMousePos()[0] < 82 && input->getMousePos()[1] > 82 && input->getMousePos()[1] < 780)
        posComList = (input->getMousePos()[1] - 82) * posComSize / (700);
    winPos.y = 82 + (700) * posComList / posComSize;
  }
  if (SDL_BlitSurface(button_sprt, &imgPos, screen, &winPos) < 0)
    throw errGraphic ("Blit Surface");
  winPos.x = screen->w - 30 - 48;
  if (posStatSize < 10)
    winPos.y = 414;
  else
  {
    if (input->getMouseClick() == 1)
      if (input->getMousePos()[0] > 1516 && input->getMousePos()[0] < 1574 && input->getMousePos()[1] > 82 && input->getMousePos()[1] < 780)
      {
        posStatList = (input->getMousePos()[1] - 82) * posStatSize / (700);
      }
    winPos.y = 82 + (700) * posStatList / posStatSize;
  }
  if (SDL_BlitSurface(button_sprt, &imgPos, screen, &winPos) < 0)
    throw errGraphic ("Blit Surface");
}

void  Interface::display()
{
  std::stringstream num;

  if (SDL_BlitSurface(back_sprt, NULL, screen, NULL) < 0)
    throw errGraphic ("Blit Surface");
  displayInput();
  scrollControl();
  menuControl();
  displayKitchenMenu(0);
  if (kitchensData.size() != 0)
    displayKitchenList(0);
  displayKitchenMenu(1);
  if (kitchensData.size() != 0)
    displayKitchenList(1);
  SDL_UpdateRect(screen, 0, 0, screen->w, screen->h);
}

void  Interface::loop()
{
  input->handle();
  display();
  input->resetMouseClick();
}
