##
## EPITECH PROJECT, 2022
## B-OOP-400-BAR-4-1-arcade-thomas.laprie
## File description:
## Makefile
##

NAME    =	arcade

CCPP    =	g++

LIBALL	=	./lib/lib_sfml.so ./lib/lib_nibbler.so ./lib/lib_snake.so

SRC_CORE 	=	./src/core/main.cpp

OBJ_CORE  	=	$(SRC_CORE:.cpp=.o)

CPPFLAGS =	-W -Wall -Wextra -g3 -I ./include

all:	$(NAME)

$(NAME):	games graphicals core

clean:
	$(MAKE) clean -C ./src/games/
	$(MAKE) clean -C ./src/graphicals/

fclean:	clean
	rm -f $(NAME) $(LIBALL)
	$(MAKE) fclean -C ./src/games/
	$(MAKE) fclean -C ./src/graphicals/


re:	fclean all

core: $(OBJ_CORE)
	$(CCPP) -o $(NAME) $(OBJ_CORE) -ldl

games: $(OBJ_GAME)
	$(MAKE) -C ./src/games/

graphicals: $(OBJ_GRAPH)
	$(MAKE) -C ./src/graphicals/

.PHONY:	all clean fclean re core games graphicals
