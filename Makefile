##
## EPITECH PROJECT, 2022
## B-OOP-400-BAR-4-1-arcade-thomas.laprie
## File description:
## Makefile
##

NAME    =	arcade

CCPP    =	g++

LIBALL	=	./lib/game/* ./lib/graph/*


SRC_CORE 	=	src/core/Core.cpp

MAIN	=	main.cpp

CPPFLAGS	=	-I ../../include

OBJ_CORE  	=	$(SRC_CORE:.cpp=.o)

CPPFLAGS =	-W -Wall -Wextra -g3 -I ./include

NFLAGS	=	-lncurses -lmenu

SFLAGS	=	-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

all:	$(NAME)

$(NAME):	games graphicals core
	cp $(LIBALL) ./lib

clean:
	$(MAKE) clean -C ./src/games/
	$(MAKE) clean -C ./src/graphicals/

fclean:	clean
	rm -f $(NAME) $(LIBALL) ./lib/*.so
	$(MAKE) fclean -C ./src/games/
	$(MAKE) fclean -C ./src/graphicals/

re:	fclean all

core: $(OBJ_CORE)
	$(CCPP) $(MAIN) -o $(NAME) $(OBJ_CORE) -ldl $(CPPFLAGS) $(NFLAGS) $(SFLAGS)

games: $(OBJ_GAME)
	$(MAKE) -C ./src/games/

graphicals: $(OBJ_GRAPH)
	$(MAKE) -C ./src/graphicals/

.PHONY:	all clean fclean re core games graphicals
