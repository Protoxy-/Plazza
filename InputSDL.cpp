#include "InputSDL.hh"

Input::Input()
{
  str = "";
  tmpStr = "";
  textReady = 0;
  end = 0;
  click = 0;
  sel = 0;
  SDL_EnableUNICODE(SDL_ENABLE);
}

Input::~Input()
{
  SDL_EnableUNICODE(SDL_DISABLE);
}

void         Input::getNextParam(SDLKey key)
{
  std::stringstream num;
  int        pos;
  int        i;

  pos = 0;
  for (i = 0; str[i]; i++)
  {
    while (str[i] == ' ')
      i++;
    if (str[i] && str[i] != ' ')
    {
      pos++;
      i++;
    }
    while (str[i] && str[i] != ' ')
    {
      if (str[i] == ';')
        pos++;
      i++;
    }
  }
  if (key == SDLK_RIGHT)
  {
    i = str.length();
    while (i > 0 && str[i] != ' ')
    {
      str.erase(i);
      i--;
    }
    if (tmpStr == "")
    {
      if (pos % 4 == 0)
        tmpStr = "\"Regina\"";
      if (pos % 4 == 1)
        tmpStr = "\"L\"";
      if (pos % 4 == 2)
        tmpStr = "\"x1\"";
      if (pos % 4 == 3)
        tmpStr = "\";\"";
    }
    if (str.length() + tmpStr.length() < 64)
      str += tmpStr.substr(1, tmpStr.length() - 2) + ' ';
    tmpStr = "";
    sel = 0;
  }
  if (key == SDLK_LEFT)
  {
    if (tmpStr == "")
    {
      i = str.length() - 1;
      while (i > 0 && str[i] == ' ')
        i--;
      while (i > 0 && str[i] != ' ' && str[i + 1] != ';')
      {
        str.erase(i);
        i--;
      }
    }
    else
    {
      tmpStr = "";
      sel = 0;
    }
  }

  if (key == SDLK_DOWN || key == SDLK_UP)
  {
  sel += (key == SDLK_DOWN ? -1 : (key == SDLK_UP ? 1 : 0));
  if (pos % 4 == 0)
  {
    if (sel < 0)
      sel = 3;
    if (sel > 3)
      sel = 0;
    switch (sel)
    {
      case 0:
        tmpStr = "\"Regina\"";
        break;
      case 1:
        tmpStr = "\"Margarita\"";
        break;
      case 2:
        tmpStr = "\"Americaine\"";
        break;
      case 3:
        tmpStr = "\"Fantasia\"";
        break;
    }
  }
  if (pos % 4 == 1)
  {
    if (sel < 0)
      sel = 4;
    if (sel > 4)
      sel = 0;
    switch (sel)
    {
      case 0:
        tmpStr = "\"S\"";
        break;
      case 1:
        tmpStr = "\"M\"";
        break;
      case 2:
        tmpStr = "\"L\"";
        break;
      case 3:
        tmpStr = "\"XL\"";
        break;
      case 4:
        tmpStr = "\"XXL\"";
        break;
    }
  }
  if (pos % 4 == 2)
  {
    if (sel <= 0)
      sel = 1;
    if (sel > 1000)
      sel = 0;
    num << sel;
    tmpStr = "\"x" + num.str() + '\"';
  }
  if (pos % 4 == 3)
  {
    tmpStr = "\";\"";
  }
}
if (str.length() + tmpStr.length() > 64)
{
  tmpStr = "";
  sel = 0;
}

}

void         Input::handleText()
{
  std::string   tmp = str;

  if (str.length() <= 64)
  {
    if (event.key.keysym.unicode == (Uint16)' ' || event.key.keysym.unicode == (Uint16)';' ||
      (event.key.keysym.unicode >= (Uint16)'0' && event.key.keysym.unicode <= (Uint16)'9') ||
      (event.key.keysym.unicode >= (Uint16)'A' && event.key.keysym.unicode <= (Uint16)'Z') ||
      (event.key.keysym.unicode >= (Uint16)'a' && event.key.keysym.unicode <= (Uint16)'z'))
      str += (char)event.key.keysym.unicode;
  }
  if (event.key.keysym.sym == SDLK_BACKSPACE && str.length() != 0)
    str.erase(str.length() - 1);
}

void         Input::handle()
{
  std::string tmp;

  if (SDL_PollEvent(&event))
  {
    switch (event.type)
    {
      case SDL_QUIT:
        end = 1;
        break;
      case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
          case SDLK_ESCAPE:
            end = 1;
            break;
          case SDLK_RETURN:
            textReady = 1;
            break;
          case SDLK_DOWN:
          case SDLK_UP:
          case SDLK_LEFT:
          case SDLK_RIGHT:
            getNextParam(event.key.keysym.sym);
            break;
          default:
            break;
        }
        if (textReady == 0)
          handleText();
        break;
      case SDL_MOUSEMOTION:
        mousePos[0] = event.motion.x;
        mousePos[1] = event.motion.y;
        break;
      case SDL_MOUSEBUTTONDOWN:
        click = 1;
        break;
      default:
        break;
    }
  }

}

std::string   Input::getString() const
{
  return (str + tmpStr);
}

void          Input::reset()
{
  textReady = 0;
  str = "";
}

int          Input::getReady() const
{
  return (textReady);
}

int          *Input::getMousePos()
{
  return (mousePos);
}

int          Input::getMouseClick() const
{
  return (click);
}

void         Input::resetMouseClick()
{
  click = 0;
}

int          Input::getEnd() const
{
  return (end);
}
