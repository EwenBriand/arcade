SRC_SFML	= 	sfml/Sfml.cpp

OBJ_SFML	=	$(SRC_SFML:.c=.o)

MAIN	=	main.c

PLACE	=	../../lib/graph/

LIBFLAG	=	-shared -fPIC

CPPFLAGS	=	-I ../../include

CFLAGS	=	-Wall -Wextra

NAME	=

all:	my_sfml

my_sfml:	$(OBJ_SFML)
	g++ -o ./lib_sfml.so $(LIBFLAG) $(OBJ_SFML) $(CPPFLAGS) $(CFLAGS) $(SFLAGS)
	mv ./lib_sfml.so $(PLACE)

clean:
	rm -rf *~
	rm -rf $(OBJ)

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
