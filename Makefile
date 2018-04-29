NAME = "RT"

SRC =	src/core/main.c \
		src/core/ini.c \
		src/core/raytracing.c \
		src/core/ft_check_object.c \
		src/core/light.c \
		src/event/key.c \
		src/event/move_object.c \
		src/event/move_object_2.c \
		src/utilities/error.c \
		src/utilities/pixel.c \
		src/utilities/free.c \
		src/utilities/free_2.c \
		src/utilities/color.c \
		src/graphics/text.c \
		src/graphics/aliasing.c \
		src/graphics/filter.c \
		src/graphics/threads.c \
		src/graphics/reflexion.c \
		src/mathematics/rotation.c \
		src/mathematics/rot_objects.c \
		src/mathematics/vect.c \
		src/mathematics/vect_2.c \
		src/mathematics/equation.c \
		src/mathematics/equation_2.c \
		src/mathematics/equation_3.c \
		src/object/sphere.c \
		src/object/plane.c \
		src/object/cone.c \
		src/object/cylinder.c \
		src/object/cube.c \
		src/object/cube_2.c \
		src/object/ellipse.c \
		src/object/tore.c \
		src/object/tore_2.c \
		src/object/parabol.c \
		src/object/normale.c \
		src/parser/parser.c \
		src/parser/sphere_p.c \
		src/parser/get_data.c \
		src/parser/plane_p.c \
		src/parser/cone_p.c \
		src/parser/cylinder_p.c \
		src/parser/cam_p.c \
		src/parser/light_p.c \
		src/parser/cube_p.c \
		src/parser/ellipse_p.c \
		src/parser/tore_p.c \
		src/parser/parabol_p.c \
		src/parser/infos.c \
		src/parser/ambiant.c \
		src/parser/inter_pln.c \
		src/texture/texture_all.c \
		src/texture/texture_checker.c \
		src/texture/texture_color1.c \
		src/texture/texture_color2.c \
		src/texture/texture_get_data.c \
		src/texture/texture_getpixelcolor.c \
		src/texture/texture_mapping.c \
		src/texture/texture_perlin1.c \
		src/texture/texture_perlin2.c \
		src/texture/texture_save_img.c \
		src/texture/texture_scale.c \
		src/texture/texture_upload.c \

LIBS = libft/libft.a

OBJ =	$(patsubst src/%.c,obj/%.o,$(SRC))

SDL2_F = -framework SDL2 -framework SDL2_ttf -framework SDL2_image -F ./frameworks/

SDL2_P = -rpath @loader_path/frameworks/

SDL2_I = -I ./frameworks/SDL2.framework/Headers

SDL2_TTF_I = -I ./frameworks/SDL2_ttf.framework/Headers

SDL2_IMG_I = -I ./frameworks/SDL2_image.framework/Headers

.SILENT :

all : $(NAME)

$(NAME) : $(OBJ)
		gcc $(LIBS) $(SDL2_F) $(OBJ) -o $(NAME) $(SDL2_P) $(SDL2_I) $(SDL2_TTF_I) $(SDL2_IMG_i)

obj/%.o: src/%.c
	mkdir -p obj
	mkdir -p obj/parser
	mkdir -p obj/object
	mkdir -p obj/mathematics
	mkdir -p obj/graphics
	mkdir -p obj/utilities
	mkdir -p obj/event
	mkdir -p obj/core
	mkdir -p obj/texture
	gcc -Wall -Wextra -Werror -c $< -o $@ -Ofast -mtune=native

clean :
	/bin/rm -rf obj

fclean : clean
	/bin/rm -rf $(NAME)

re : fclean all

.PHONY: clean fclean
