# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/05 18:48:08 by kennyduong        #+#    #+#              #
#    Updated: 2022/04/28 12:07:39 by smagdela         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#########################################
#				PROGRAMS				#
#########################################
NAME		=	minishell

#########################################
#				COMMANDS				#
#########################################
CC			=	clang -g
MKDIR		=	mkdir -p
AR			=	ar rcs
RM			= 	rm -rf

#########################################
#				COLORS					#
#########################################
GREY		=	$'\033[0;30m
RED			=	$'\033[0;31m
GREEN		=	$'\033[0;92m
YELLOW		=	$'\033[0;33m
BLUE		=	$'\033[0;34m
U_BLUE		=	$'\033[4;34m
PURPLE		=	$'\033[0;35m
CYAN		=	$'\033[0;96m
WHITE		=	$'\033[0;37m
END			=	$'\033[0;m
BOLD		=	$'\033[1m

#########################################
#			FLAGS COMPILATION			#
#########################################
CFLAGS		=	-Wall -Wextra -Werror
DEBUG		=	-fsanitize=address -g3

INC			=	-I includes $(INC_LFT)
INC_LFT		=	-I libft/inc

LINK		=	$(LINK_LFT) -lreadline
LINK_LFT	=	-L ./libft -lft

#########################################
#			DIRECTORIES					#
#########################################
SRC_DIR		=	srcs/
OBJ_DIR		=	obj/
LIBFT_DIR	=	libft/

#########################################
#			LIBRARIES					#
#########################################
LIBFT		=	$(LIBFT_DIR)libft.a

#########################################
#			SOURCES	FILES				#
#########################################
MS_SRC		=	main.c				utils.c				data_init.c\
				data_utils.c		signal.c\
				${addprefix parsing/,\
					lexer.c				scanner.c			categorizer.c\
					analyzer.c			parsing_utils.c		parsing_utils_2.c\
					parsing_utils_3.c	checker_quotes.c	checker_redir.c\
					checker_words.c		expand_reduce.c		parsing_utils_4.c}\
				${addprefix builtins/,\
					echo.c				env.c				exit.c\
					export.c			pwd.c				unset.c\
					cd.c				export_utils.c}\
				${addprefix execution/,\
					exec.c				pipeline.c			pipeline_utils.c\
					exec_utils.c		heredoc.c			file_handler_utils.c\
					pipeline_utils_2.c	heredoc_utils.c		exec_builtins.c}

#########################################
#            OBJECT FILES    	        #
#########################################
MS_OBJ		=	$(MS_SRC:.c=.o)
MS_OBJ		:=	$(addprefix $(OBJ_DIR), $(MS_OBJ))

#########################################
#			MAKE	RULES				#
#########################################

$(NAME): $(OBJ_DIR) $(MS_OBJ) $(LIBFT)
	@echo "> $(CYAN)Generate objects$(END) : \t\t[$(GREEN)OK$(END)]"
	@$(CC) $(LINK) -o $@ $(MS_OBJ) $(LIBFT)
	@echo "> $(WHITE)$(BOLD)MiniShell Compilation$(END) : \t[$(YELLOW)COMPLETE$(END)]"

$(LIBFT):
	@make -s -C $(LIBFT_DIR)
	@make -s -C $(LIBFT_DIR) clean
	@echo "> $(CYAN)Libft Compilation$(END) : \t\t[$(GREEN)OK$(END)]"

${OBJ_DIR}%.o:	${SRC_DIR}%.c
	@${MKDIR} ${@D}
	@${CC} ${CFLAGS} ${INC} -c -o $@ $<

$(OBJ_DIR):
	@$(MKDIR) $(OBJ_DIR)

all: $(NAME)

bonus :	
	
clean:
	@$(RM) $(OBJ_DIR)
	@echo "> $(PURPLE)Clean objects$(END) : \t\t[$(GREEN)OK$(END)]"
	
fclean: clean
	@$(RM) $(NAME)
	@echo "> $(PURPLE)Delete Program$(END) : \t\t[$(GREEN)OK$(END)]"
	@make -s -C $(LIBFT_DIR) fclean
	@echo "> $(PURPLE)Delete LIBFT$(END) : \t\t[$(GREEN)OK$(END)]"
	
re: fclean all 

norm:
	@norminette ${SRC_DIR} ${INC_DIR} | grep 'Error' ; true

leak:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=ignorereadline ./${NAME}

fds:
	valgrind --track-fds=yes --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=ignorereadline ./${NAME}

.PHONY: all clean fclean re
