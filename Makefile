NAME = snake

CC = c++

CFLAGS = -Wall -Wextra -Werror -ggdb3 -O0 -std=c++98 -lm `sdl2-config --cflags`

LDFLAGS = `sdl2-config --libs` -lSDL2_mixer -lSDL2_image -lSDL2_ttf

SRC =	./main.cpp	

OBJECTS = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME) $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re