

NAME	=	gomoku

SRC	=	main.cpp \
		Core.cpp \
		View.cpp \
		Model.cpp \
		Player.cpp \
		f3libre.cpp \
		Bouton.cpp \

OBJ	=	$(SRC:.cpp=.o)

ifeq ($(DEBUG), 1)
	CXXFLAGS += -g
endif

CXXFLAGS +=	-Wall -Wextra -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system \
		-std=c++14 -Wno-deprecated-declarations -lpthread

all	:	$(NAME)

$(NAME)	:	$(OBJ)
		g++ -o $(NAME) $(OBJ) $(CXXFLAGS)

clean	:
		rm -f $(OBJ)

fclean	:	clean
		rm -f $(NAME)

re	:	fclean all
