NAME = hotrace
SRC = main.c get_next_line.c get_next_line_utils.c

OBJ_DIR = ./dir/
OBJ = $(SRC:%.c=$(OBJ_DIR)%.o)
DEPS = $(OBJ:.o=.d)

CC = cc #-fsanitize=address,bounds,undefined,float-divide-by-zero
CFLAGS = -Wall -Wextra -Werror -MMD -MP -g -O3 -flto -march=native

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ) 
	$(CC) $(OBJ) $(CFLAGS) -o $(NAME)

$(OBJ_DIR)%.o : %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

clean:
	rm -rf $(OBJ) $(DEPS) $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME) $(OBJ_DIR) minirt

re: fclean all

# Include auto-generated dependency files
-include $(DEPS)

# clang-tidy -checks='-*,performance-*,clang-analyzer-*' \
# main.c camera/*.c intersections/*.c parser/*.c render/*.c texture/*.c utils/*.c vectors/*.c -- -I./include
.PHONY: all clean fclean re
