# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/27 15:51:12 by jwalsh            #+#    #+#              #
#    Updated: 2017/03/02 16:57:18 by jwalsh           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RTv1
LIBFT_NAME = libft.a
LIBMATHFT_NAME = libmathft.a

SRC_PATH = src/
INC_PATH = inc/
LIB_PATH = Libft/
LIBMATH_PATH = Libmathft/

PARSING = 	check_data \
			error_line_exit \
			get_color \
			get_file.1 \
			get_token \
			init_parse_tools \
			parse_input.1 \
			parse_value \
			reset_attributes.1 \
			set_default \
			rt_error \
			set_attributes.1 \
			split_trim \

SRC = 		main.1 \
			debug.1
			
LIST = 		get_new_camera \
			get_new_light \
			get_new_object.1 \
			get_new_scene.1 \
			init_color_list \
			input_new \
			input_pushback \
			push_camera \
			push_light \
			push_object \
			push_scene 

OBJ_DIR = obj

EXT = .c

SRC_PARSING = $(addsuffix $(EXT), $(PARSING))
SRC_LST = $(addsuffix $(EXT), $(LIST))
SRC_SRC = $(addsuffix $(EXT), $(SRC))

OBJ_SRC = $(addprefix $(OBJ_DIR)/, $(SRC_SRC:.c=.o))
OBJ_LST = $(addprefix $(OBJ_DIR)/, $(SRC_LST:.c=.o))
OBJ_PARSING = $(addprefix $(OBJ_DIR)/, $(SRC_PARSING:.c=.o))

CC	= gcc
FLG = -Werror -Wextra -Wall
SDL = `~/.brew/bin/sdl2-config --libs`
#add after FLG on line 74

C_NONE = \033[0m
C_BOLD = \033[1m
C_BLACK = \033[30m
C_RED = \033[31m
C_GREEN = \033[32m
C_BROWN = \033[33m
C_BLUE = \033[34m
C_MAGENTA = \033[35m
C_CYAN = \033[36m
C_GRAY = \033[37m

ECHO = echo

all: $(NAME)

$(NAME): $(OBJ_SRC) $(OBJ_PARSING) $(OBJ_LST)
	@make -C $(LIB_PATH)
	@make -C $(LIBMATH_PATH)
	@$(CC) $(FLG) $(SDL) -g $(LIB_PATH)$(LIBFT_NAME) $(LIBMATH_PATH)$(LIBMATHFT_NAME) $(OBJ_PARSING) $(OBJ_SRC) $(OBJ_LST) -o $(NAME)
	@$(ECHO) "$(C_GREEN)RTv1 compilation done.$(C_NONE)"

$(OBJ_DIR)/%.o : ./src/%.c
	@/bin/mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -g -I./inc -c -o $@ $<

$(OBJ_DIR)/%.o : ./src/parsing/%.c
	@/bin/mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -g -I./inc -c -o $@ $<

$(OBJ_DIR)/%.o : ./src/list/%.c
	@/bin/mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -g -I./inc -c -o $@ $<

clean:
	@/bin/rm -Rf $(OBJ_DIR)
	@make -C $(LIB_PATH) clean
	@make -C $(LIBMATH_PATH) clean
	@$(ECHO) "$(C_GREEN)RTv1 clean done.$(C_NONE)"

fclean: clean
	@/bin/rm -f $(NAME)
	@make -C $(LIB_PATH) fclean
	@make -C $(LIBMATH_PATH) fclean
	@$(ECHO) "$(C_GREEN)RTv1 fclean done.$(C_NONE)"

re: fclean all

PHONY : re all clean fclean
	@$(ECHO) "$(C_GREEN)RTv1 .PHONY done.$(C_NONE)"

.PHONY: all clean fclean re
