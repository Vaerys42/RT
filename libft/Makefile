# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/08 16:09:33 by kboucaud          #+#    #+#              #
#    Updated: 2016/11/21 17:41:37 by kboucaud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = get_next_line.c ft_strjoin_free.c ft_strnjoin.c ft_strndup.c ft_lstadd.c \
ft_lstmap.c ft_lstdel.c ft_lstiter.c ft_lstnew.c ft_lstdelone.c ft_strrev.c \
ft_strsplit.c ft_itoa.c ft_strtrim.c ft_atoi.c ft_bzero.c ft_isalpha.c \
ft_isalnum.c ft_isascii.c ft_isdigit.c  ft_isprint.c ft_memalloc.c \
ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memdel.c ft_memmove.c \
ft_memset.c ft_putchar.c ft_putchar_fd.c ft_putendl.c ft_putendl_fd.c \
ft_putnbr.c ft_putnbr_fd.c ft_putstr.c ft_putstr_fd.c ft_strcat.c ft_strchr.c \
ft_strclr.c  ft_strcmp.c ft_strcpy.c ft_strdel.c ft_strdup.c ft_strequ.c \
ft_striter.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlen.c ft_strmap.c \
ft_strmapi.c ft_strncat.c ft_strncmp.c ft_strncpy.c ft_strnequ.c ft_strnew.c \
ft_strnstr.c ft_strrchr.c ft_strstr.c ft_strsub.c ft_tolower.c ft_toupper.c \
ft_atof.c ft_malloc_error.c ft_freetab.c\

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : 
		gcc -c -Wall -Wextra -Werror $(SRC)
		ar rc $(NAME) $(OBJ)

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -rf $(NAME)

re : fclean all
