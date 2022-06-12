##
## EPITECH PROJECT, 2022
## plazza
## File description:
## Makefile
##

SRC		=	src/main.cpp				\
			src/Shell/Shell.cpp			\
			src/Plazza/Plazza.cpp		\
			src/IPC/IPC.cpp				\
			src/IPC/encapsMsgQueues.cpp	\
			src/Kitchen/Kitchen.cpp		\
			src/Reception/Reception.cpp	\
			src/Reception/fork.cpp		\

CXXFLAGS	=	-std=c++20 -Wall -Wextra -I include

OBJ		=	$(SRC:.cpp=.o)

LIB		=	-pthread -lrt

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