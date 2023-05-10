NAME =		philo
FILES =		clean.c \
			death_check.c \
			dining_color.c \
			dining_white.c \
			error.c \
			init.c \
			init_philo.c \
			main.c \
			message.c \
			philo.c \
			time.c \
			utils.c
HEADER =	incl/philo.h
SRC_PATH =	src
OBJ_PATH =	obj

SRC = $(addprefix $(SRC_PATH)/,$(FILES))
OBJ = $(addprefix $(OBJ_PATH)/,$(FILES:.c=.o))

FLAGS = -Wall -Wextra -Werror 
SANITIZE = -g -fsanitize=thread -static-libsan

.PHONY: all clean fclean re

all: $(NAME)

$(OBJ_PATH):
	@mkdir $(OBJ_PATH)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c | $(OBJ_PATH)
#	@cc $(FLAGS) -c $< -o $@
	@cc $(SANITIZE) $(FLAGS) -c $< -o $@

$(NAME): $(OBJ)
#	@cc $(OBJ) -o $(NAME) -I $(HEADER)
	@cc $(SANITIZE) $(OBJ) -o $(NAME) -I $(HEADER)
	@clear

clean:
	@rm -rf $(OBJ_PATH)

fclean: clean
	@rm $(NAME)

re: fclean all