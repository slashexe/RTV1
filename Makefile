.PHONY: clean $(NAME) fclean re all

NAME	= rtv1

SRC		= 	srcs/controleur/main.c		\
			srcs/controleur/read_conf.c \
			srcs/view/draw.c			\
			srcs/model/hit_sphere.c		\
			srcs/model/math.c

OBJ		= $(patsubst src/%.c,obj/%.o,$(SRC))

all: $(NAME)

$(NAME): $(OBJ) include/rtv1.h
		make -C libft/
		gcc -Wall -Wextra -Werror -L libft/ -lft -g -L ~/.brew/Cellar/sdl2/2.0.8/lib/ -lSDL2 -framework OpenGL -framework AppKit $(SRC) -o $(NAME)

obj/%.o: src/%.c
		mkdir -p obj
		gcc -Wall -Wextra -Werror -c $< -o $@

clean:
		/bin/rm -rf obj/
		make -C libft/ clean

fclean: clean
		/bin/rm -f $(NAME)
		make -C libft/ fclean

re: fclean all

test: re
		./$(NAME)

all: $(NAME)
