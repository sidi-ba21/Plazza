##
## EPITECH PROJECT, 2022
## plazza
## File description:
## Makefile
##

SRC		=	src/main.cpp \

CXXFLAGS	=	-std=c++20 -Wall -Wextra -pthread -I include

OBJ		=	$(SRC:.cpp=.o)

NAME	=	plazza

all:	$(NAME)

$(NAME):$(OBJ)
	g++ $(OBJ) -o $(NAME) $(LIB)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re