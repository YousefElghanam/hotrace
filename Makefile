NAME = hotrace
SRC = main.c main_utils.c hashmap_funcs.c hashmap_funcs2.c utils.c

OBJ_DIR = ./dir/
OBJ = $(SRC:%.c=$(OBJ_DIR)%.o)
DEPS = $(OBJ:.o=.d)

CC = cc #-fsanitize=address,bounds,undefined,float-divide-by-zero
CFLAGS = -Wall -Wextra -Werror -Wno-unused-result -MMD -MP -g #-O3 -flto -march=native

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ) 
	$(CC) $(OBJ) $(CFLAGS) -o $(NAME)

$(OBJ_DIR)%.o : %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

run: re
	./$(NAME) <pairs.txt

val: re
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) <test/testfile

cache: re
	valgrind --tool=cachegrind ./$(NAME) <test/testfile

time: re
	time ./$(NAME) <test/testfile

clean:
	rm -rf $(OBJ) $(DEPS) $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME) $(OBJ_DIR)

re: fclean all

# Include auto-generated dependency files
-include $(DEPS)

# clang-tidy -checks='-*,performance-*,clang-analyzer-*' \
# main.c camera/*.c intersections/*.c parser/*.c render/*.c texture/*.c utils/*.c vectors/*.c -- -I./include
.PHONY: all clean fclean re
