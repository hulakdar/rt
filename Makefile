CC=clang
CFLAGS=-Werror -Wall -Wextra -g -Iincludes/
OS := $(shell uname)
ifeq ($(OS), Darwin)
FRAMEWORKS= -framework OpenCL
else
FRAMEWORKS= -lSDL2 -lOpenCL
endif
FILES=main
OBJ=$(addprefix obj/, $(addsuffix .o, $(FILES)))
NAME=RT

all: $(NAME)

$(NAME): $(OBJ) libft/libft.a
	@$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(FRAMEWORKS) libft/libft.a
	@echo "Binary is done! 🖥"
obj/%.o: src/%.c
	@$(CC) -c $^ -o $@ $(CFLAGS)
clean:
	@rm -f $(OBJ)
	@echo "Cleaned the objects! ❌"
fclean: clean
	@rm -f $(NAME)
	@echo "Cleaned the binary! ☠️"
re: fclean all
	
.PHONY: clean fclean re
