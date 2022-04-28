# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/22 15:57:00 by chduong           #+#    #+#              #
#    Updated: 2022/03/08 16:08:28 by smagdela         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= 	libft.a

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror
INC			=	-I inc

AR			=	ar rcs
RM			= 	rm -rf
MKDIR		=	mkdir -p

SRC_DIR		=	srcs/
SRC			=	ft_atoi.c			ft_isalnum.c		ft_isdigit.c\
				ft_lstadd_back.c	ft_lstdelone.c		ft_strcmp.c\
				ft_memccpy.c		ft_memcpy.c			ft_putchar_fd.c\
				ft_putstr_fd.c		ft_strdup.c			ft_strlcpy.c\
				ft_strncmp.c		ft_strtrim.c		ft_toupper.c\
				ft_bzero.c			ft_isalpha.c		ft_isprint.c\
				ft_lstadd_front.c	ft_lstiter.c		ft_lstnew.c\
				ft_memchr.c			ft_memmove.c		ft_putendl_fd.c\
				ft_split.c			ft_strjoin.c		ft_strlen.c\
				ft_strnstr.c		ft_substr.c			get_next_line.c\
				ft_calloc.c			ft_isascii.c		ft_itoa.c		\
				ft_lstclear.c		ft_lstlast.c		ft_lstsize.c\
				ft_memcmp.c			ft_memset.c			ft_putnbr_fd.c\
				ft_strchr.c			ft_strlcat.c		ft_strmapi.c\
				ft_strrchr.c		ft_tolower.c		get_next_line_utils.c

OBJ_DIR		=	obj/
OBJ			=	$(SRC:.c=.o)
OBJ			:=	$(addprefix $(OBJ_DIR), $(OBJ))

$(NAME):	$(OBJ_DIR) $(OBJ)
	$(AR) $(NAME) $(OBJ)

${OBJ_DIR}%.o:	${SRC_DIR}%.c
	${CC} ${CFLAGS} ${INC} -c -o $@ $<

$(OBJ_DIR):
	$(MKDIR) $(OBJ_DIR)

all:		$(NAME)

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
