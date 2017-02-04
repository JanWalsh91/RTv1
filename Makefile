# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/27 15:51:12 by jwalsh            #+#    #+#              #
#    Updated: 2017/02/04 17:10:58 by jwalsh           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RTv1
LIBFT_NAME = libft.a
LIBMATHFT_NAME = libmathft.a

SRC_PATH = src/
INC_PATH = inc/
LIB_PATH = Libft/
LIBMATH_PATH = Libmathft/

SRC_NAME =	main \
			draw_image \
			extract_cameras \
			extract_lights \
			get_file \
			get_new_object \
			get_new_scene \
			handle_sdl_events \
			init_attributes \
			init_sdl \
			parse_attributes_1 \
			parse_color \
			parse_input \
			push_camera \
			push_light \
			push_object \
			push_scene \
			reset_attributes \
			rtv1 \
			set_attributes \
			split_trim \
			trace_camera_ray \
			debug

SRC_NAME_PATH = $(addprefix $(SRC_PATH), $(SRC_NAME))
SRC = $(addsuffix $(EXT), $(SRC_NAME_PATH))

OBJ = $(SRC:.c=.o)

EXT = .c
CC	= gcc
FLG = -Werror -Wextra -Wall -Ofast
SDL = `sdl2-config --libs`
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

%.o : %.c
	@$(CC) $(FLG) -I$(INC_PATH) -I$(LIB_PATH) -I$(LIBMATH_PATH) -c -o $@ $^

$(NAME): $(OBJ)
	@make -C $(LIB_PATH)
	@make -C $(LIBMATH_PATH)
	@$(CC) $(FLG) $(SDL) -lpthread $(LIB_PATH)$(LIBFT_NAME) $(LIBMATH_PATH)$(LIBMATHFT_NAME) $(OBJ) -o $(NAME)
	@$(ECHO) "$(C_GREEN)RTv1 compilation done.$(C_NONE)"

clean:
	@/bin/rm -f $(OBJ)
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
