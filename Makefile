NAME =		philo
FILES =		main.c \
			error.c \
			init.c \
			philo.c \
			clean.c \
			time.c
HEADER =	incl/philo.h
SRC_PATH =	src
OBJ_PATH =	obj

SRC = $(addprefix $(SRC_PATH)/,$(FILES))
OBJ = $(addprefix $(OBJ_PATH)/,$(FILES:.c=.o))

FLAGS = -Wall -Wextra -Werror

.PHONY: all tmp clean fclean re

all: tmp $(NAME)

tmp:
	@mkdir $(OBJ_PATH)

obj/%.o: src/%.c
	@cc $(FLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@cc $(OBJ) -o $(NAME) -I $(HEADER)
	@clear

clean:
	@rm -rf $(OBJ_PATH)

fclean: clean
	@rm $(NAME)

re: fclean all