##
## EPITECH PROJECT, 2022
## B-OOP-400-BAR-4-1-arcade-thomas.laprie
## File description:
## Makefile
##

NAME    =	arcade

CCPP    =	g++

SRC_GAME 	=	./src/games/test.cpp

SRC_GRAPH 	=	./src/graphicals/test.cpp

SRC_CORE 	=	./src/core/main.cpp

OBJ_CORE  	=	$(SRC_CORE:.cpp=.o)

OBJ_GRAPH   =	$(SRC_GRAPH:.cpp=.o)

OBJ_GAME  	=	$(SRC_GAME:.cpp=.o)

CPPFLAGS =	-W -Wall -Wextra -g3 -I ./include

all:	$(NAME)

$(NAME):	games graphicals core

clean:
	rm -f $(OBJ_CORE) $(OBJ_GAME) $(OBJ_GRAPH)

fclean:	clean
	rm -f $(NAME) libgames.so libgraphicals.so


re:	fclean all

core: $(OBJ_CORE)
	$(CCPP) -o $(NAME) $(OBJ_CORE) -ldl

games: $(OBJ_GAME)
	$(CCPP) -o libgames.so -shared -fPIC $(OBJ_GAME)

graphicals: $(OBJ_GRAPH)
	$(CCPP) -o libgraphicals.so -shared -fPIC $(OBJ_GRAPH)

.PHONY:	all clean fclean re core games graphicals