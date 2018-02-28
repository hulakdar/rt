CC=clang
CFLAGS=-Werror -Wall -Wextra -O3 -Iincludes/
OS := $(shell uname)
ifeq ($(OS), Darwin)
FRAMEWORKS= -lmlx -framework OpenGL -framework AppKit
else
FRAMEWORKS= -lmlx -lXext -lX11 -lm
endif
FILES=main rt_draw rt_handler rt_trace rt_construct_ray rt_intersect ray_normalize point_substract dot_product rt_helpers rt_solve_quadratic rt_get_intersect rt_normal rt_shade rt_operations rt_rotations rt_scene_1 rt_scene_2 rt_scene_3 rt_scene_4 rt_scene_5 rt_scene_6 rt_scene_7 rt_scene_8 rt_scene_9 rt_scene_10 rt_scene_11 rt_scene_12
OBJ=$(addprefix obj/, $(addsuffix .o, $(FILES)))
NAME=RTv1

all: $(NAME)

$(NAME): $(OBJ) libft/libft.a
	@$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(FRAMEWORKS) libft/libft.a
	@echo "Binary is done! 🖥"
libft/libft.a:
	@make -C libft/
	@echo "Library is done!📚"
obj/%.o: src/%.c
	@$(CC) -c $^ -o $@ $(CFLAGS)
clean:
	@rm -f $(OBJ)
	@make -C libft/ clean
	@echo "Cleaned the objects! ❌"
fclean: clean
	@rm -f $(NAME)
	@make -C libft/ fclean
	@echo "Cleaned the binary! ☠️"
re: fclean all
	
.PHONY: clean fclean re
