SRC_SNK	= 	snake/GameSnake.cpp

OBJ_SNK	=	$(SRC_SNK:.c=.o)

SRC_NIB	= 	nibbler/Nibbler.cpp

OBJ_NIB	=	$(SRC_NIB:.c=.o)

MAIN	=	main.c

PLACE	=	../../lib/game/

LIBFLAG	=	-shared -fPIC

CPPFLAGS	=	-I ../../include

CFLAGS	=	-Wall -Wextra

NAME	=

all:	my_snake my_nibbler

my_nibbler:	$(OBJ_NIB)
	g++ -o ./lib_nibbler.so $(LIBFLAG) $(OBJ_NIB) $(CPPFLAGS) $(CFLAGS) $(SFLAGS)
	mv ./lib_nibbler.so $(PLACE)

my_snake:	$(OBJ_SNK)
	g++ -o ./lib_snake.so $(LIBFLAG) $(OBJ_SNK) $(CPPFLAGS) $(CFLAGS) $(SFLAGS)
	mv ./lib_snake.so $(PLACE)

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
