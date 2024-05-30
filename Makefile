# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: miguelro <miguelro@students.42lisboa.com>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/28 17:00:30 by marvin            #+#    #+#              #
#    Updated: 2023/09/10 12:10:37 by miguelro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#----- Executable Name-------------
NAME = minishell

#----- Colors----------------------
DEFAULT = \033[0;39m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m

#----- Flags ----------------------
CC = gcc 
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address 

#----- libft----------------------
LIBFT = ./Libft/libft.a
LIBFT_PATH = ./Libft

#----- Paths----------------------
INCLUDES = -I ./headers/
SRC_PATH = ./sources
OBJ_PATH = ./objects

BUILTINS = echo.c cd.c pwd.c env.c exit.c export.c unset.c  \

EXECUTER = executer.c executer_path.c here_doc.c redirections.c\

PARSER = parser.c dollar.c lexer.c super_split.c\

UTILS = builtin_utils.c export_utils.c export_utils2.c utils.c terminate.c\
		executer_utils.c dollar_utils.c red_utils.c red_utils_2.c utils2.c\
		signal.c executer_utils_2.c red_utils_3.c\

SRC_NAME = 	main.c \

#----- Files----------------------

SRC = $(addprefix $(SRC_PATH)/, $(SRC_NAME)) \
      $(addprefix $(SRC_PATH)/builtins/, $(BUILTINS)) \
	  $(addprefix $(SRC_PATH)/executer/, $(EXECUTER)) \
	  $(addprefix $(SRC_PATH)/parser/, $(PARSER)) \
	  $(addprefix $(SRC_PATH)/utils/, $(UTILS)) 

OBJS = $(addprefix $(OBJ_PATH)/, $(SRC_NAME:.c=.o)) \
       $(addprefix $(OBJ_PATH)/builtins/, $(BUILTINS:.c=.o)) \
	   $(addprefix $(OBJ_PATH)/executer/, $(EXECUTER:.c=.o)) \
	   $(addprefix $(OBJ_PATH)/parser/, $(PARSER:.c=.o)) \
	   $(addprefix $(OBJ_PATH)/utils/, $(UTILS:.c=.o))


#----- Compilation----------------------
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT) -lreadline -o $(NAME)
	clear
	@echo "$(GREEN)$(NAME) compiled $(DEFAULT)"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c | $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_PATH)/builtins/%.o: $(SRC_PATH)/builtins/%.c | $(OBJ_PATH)/builtins
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_PATH)/executer/%.o: $(SRC_PATH)/executer/%.c | $(OBJ_PATH)/executer
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	
$(OBJ_PATH)/parser/%.o: $(SRC_PATH)/parser/%.c | $(OBJ_PATH)/parser
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_PATH)/utils/%.o: $(SRC_PATH)/utils/%.c | $(OBJ_PATH)/utils
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

#----- Create Objects----------------------
$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

$(OBJ_PATH)/builtins:
	@mkdir -p $(OBJ_PATH)/builtins

$(OBJ_PATH)/executer:
	@mkdir -p $(OBJ_PATH)/executer

$(OBJ_PATH)/parser:
	@mkdir -p $(OBJ_PATH)/parser

$(OBJ_PATH)/utils:
	@mkdir -p $(OBJ_PATH)/utils

$(LIBFT):
	@$(MAKE) -s -C $(LIBFT_PATH)

clean:
	@$(MAKE) -s -C $(LIBFT_PATH) clean
	@$(RM) -rf $(OBJ_PATH)
	@echo "------------------------"
	@echo "\n$(RED)cleaning objects\n$(DEFAULT)"
	@echo "------------------------"

fclean: clean
	@$(MAKE) -s -C $(LIBFT_PATH) fclean
	@$(RM) -f $(NAME)

re: fclean all

m: re 
	./minishell
v: re
	clear
	valgrind valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
		 --log-file=valgrind-out.txt \
		 --suppressions=read.supp \
		 --track-fds=yes \
		 ./minishell

.PHONY: all re clean fclean m	
