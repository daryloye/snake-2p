NAME = snake

CC = c++

CXXFLAGS = -Wall -Werror -Wextra

SRC = ./main.cpp

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
		   $(CC) $(CXXFLAGS) $(OBJ) -o $(NAME) -lncurses

%.o: %.cpp
	$(CC) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
