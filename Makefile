NAME = "RT"

SRC =	src/main.c \
		src/ini.c \
		src/error.c \
		src/key.c \
		src/vect.c \
		src/vect_2.c \
		src/raytracing.c \
		src/ft_check_object.c \
		src/sphere.c \
		src/plane.c \
		src/parser.c \
		src/get_data.c \
		src/cone.c \
		src/sphere_p.c \
		src/plane_p.c \
		src/cone_p.c \
		src/cylinder_p.c \
		src/cylinder.c \
		src/rotation.c \
		src/cam_p.c \
		src/light_p.c \
		src/cube.c \
		src/cube_p.c \
		src/aliasing.c \
		src/equation.c \
		src/ellipse.c \
		src/ellipse_p.c \
		src/filter.c \
		src/pixel.c \
		src/move_object.c \

LIBS = libft/libft.a SDL2.framework/SDL2

OBJ =	$(patsubst src/%.c,obj/%.o,$(SRC))

.SILENT :

all : $(NAME)

$(NAME) : $(OBJ)
		gcc $(LIBS) $(OBJ) -o $(NAME)

obj/%.o: src/%.c
	mkdir -p obj
	gcc -Wall -Wextra -Werror -c $< -o $@

clean :
	/bin/rm -rf obj

fclean : clean
	/bin/rm -rf $(NAME)

re : fclean all

.PHONY: clean fclean
