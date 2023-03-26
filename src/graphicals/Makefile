SRC_SFML	= 	sfml/Sfml.cpp

OBJ_SFML	=	$(SRC_SFML:.c=.o)

SRC_SDL	= 	sdl/DisplaySDL2.cpp

OBJ_SDL	=	$(SRC_SDL:.c=.o)

SRC_NCR	= 	ncurse/Ncurse.cpp

OBJ_NCR	=	$(SRC_NCR:.c=.o)

MAIN	=	main.c

PLACE	=	../../lib/graph/

LIBFLAG	=	-shared -fPIC

CPPFLAGS	=	-I ../../include

NFLAGS	=	-lncurses -lmenu

SFLAGS	=	-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

SDLFLAGS	=	-lSDL2 -lSDL2_ttf -lSDL2_mixer

CFLAGS	=	-Wall -Wextra

NAME	=

all:	my_ncurses my_sdl

my_sfml:	$(OBJ_SFML)
	g++ -o ./lib_sfml.so $(LIBFLAG) $(OBJ_SFML) $(CPPFLAGS) $(CFLAGS) $(SFLAGS)
	mv ./lib_sfml.so $(PLACE)

my_ncurses:	$(OBJ_NCR)
	g++ -o ./lib_ncurse.so $(LIBFLAG) $(OBJ_NCR) $(CPPFLAGS) $(CFLAGS) $(NFLAGS)
	mv ./lib_ncurse.so $(PLACE)

my_sdl:	$(OBJ_SDL)
	g++ -o ./lib_sdl.so $(LIBFLAG) $(OBJ_SDL) $(CPPFLAGS) $(CFLAGS) $(SDLFLAGS)
	mv ./lib_sdl.so $(PLACE)

clean:
	rm -rf *~

fclean: clean
	rm -f $(NAME)
	rm -rf *.a

re: fclean all

unitest: CFLAGS += -lcriterion
unitest:
	gcc -o $(NAME) $(CPPFLAGS) $(LDFLAGS) $(CFLAGS)

debug: CFLAGS += -g3
debug: all

.PHONY: all makelib clean fclean re unitest debug
