##
## Makefile for Nibbler in /home/hoerte_f/rendu/cpp_nibbler
##
## Made by Francois Hoertel
## Login   <hoerte_f@epitech.net>
##
## Started on  Wed Mar 11 17:36:34 2015 Francois Hoertel
## Last update Sun Apr 26 23:40:05 2015 Francois Hoertel
##

CC	= g++

SRC	= Exception.cpp \
	  System.cpp \
	  Processes.cpp \
	  Thread.cpp \
	  Mutex.cpp \
	  CondVar.cpp \
	  NamedPipe.cpp \
	  Factory.cpp \
	  InputSDL.cpp \
	  InterfaceSDL.cpp \
	  Pizza.cpp \
	  PizzaRegina.cpp \
	  PizzaMargarita.cpp \
	  PizzaAmericaine.cpp \
	  PizzaFantasia.cpp \
	  Cook.cpp \
	  KitchenData.cpp \
	  Kitchen.cpp \
	  Reception.cpp \
	  Main.cpp

OBJS	= $(SRC:.cpp=.o)

LDFLAGS = -ldl -l pthread

NAME	= plazza

RM	= rm -rf

all	: $(NAME)

$(NAME)	: $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS) -lSDL -lSDL_image -lSDL_ttf

clean	:
	$(RM) $(OBJS) $(PIPEFILE)

fclean	: clean
	$(RM) $(NAME)

re	: fclean all
