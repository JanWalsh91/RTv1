# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/27 15:51:12 by jwalsh            #+#    #+#              #
#    Updated: 2017/03/23 11:51:19 by jwalsh           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RTv1
LIBFT_NAME = libft.a
LIBMATHFT_NAME = libmathft.a

SRC_PATH = src/
INC_PATH = inc/
LIB_PATH = Libft/
LIBMATH_PATH = Libmathft/

SRC = 		main \
			rtv1

SDL = 		handle_sdl_events \
			init_sdl

PARSING = 	get_color \
			get_file \
			get_token \
			init_parse_tools \
			init_tokens \
			init_color_list \
			parse_color_name \
			parse_input \
			parse_value_1 \
			parse_value_2 \
			parse_value_3 \
			parse_value_4 \
			parse_value_5 \
			parse_value_6 \
			parse_value_7 \
			parse_value_8 \
			parse_value_9 \
			parse_vector \
			parse_double \
			reset_attributes \
			set_attributes_1 \
			set_attributes_2 \
			split_trim \

DATA_PREP = check_scenes \
			check_objects \
			init_cameras \
			set_default_1 \
			set_default_2 \
			set_default_3 \
			set_default_4

LIST = 		get_new_camera \
			get_new_light \
			get_new_object \
			get_new_scene \
			get_new_input \
			input_pushback \
			push_camera \
			push_light \
			push_object \
			push_scene 

RAY_TRACING = cast_primary_ray \
			render \
			get_normal \
			init_camera_ray \
			solve_quadratic \
			intersects \
			get_plane_intersection \
			get_sphere_intersection \
			get_disk_intersection \
			get_cylinder_intersection \
			get_cone_intersection \
			in_shadow \
			get_diffuse \
			get_specular \
			get_ambient \
			reflect

MISC = 		debug \
			free_parse_tools \
			free_scenes \
			rt_error

OBJ_DIR = obj

EXT = .c

SRC_SRC = $(addsuffix $(EXT), $(SRC))
SRC_SDL = $(addsuffix $(EXT), $(SDL))
SRC_PARSING = $(addsuffix $(EXT), $(PARSING))
SRC_DATA = $(addsuffix $(EXT), $(DATA_PREP))
SRC_RT = $(addsuffix $(EXT), $(RAY_TRACING))
SRC_LST = $(addsuffix $(EXT), $(LIST))
SRC_MISC = $(addsuffix $(EXT), $(MISC))

OBJ_SRC = $(addprefix $(OBJ_DIR)/, $(SRC_SRC:.c=.o))
OBJ_SDL = $(addprefix $(OBJ_DIR)/, $(SRC_SDL:.c=.o))
OBJ_PARSING = $(addprefix $(OBJ_DIR)/, $(SRC_PARSING:.c=.o))
OBJ_DATA = $(addprefix $(OBJ_DIR)/, $(SRC_DATA:.c=.o))
OBJ_RT = $(addprefix $(OBJ_DIR)/, $(SRC_RT:.c=.o))
OBJ_LST = $(addprefix $(OBJ_DIR)/, $(SRC_LST:.c=.o))
OBJ_MISC = $(addprefix $(OBJ_DIR)/, $(SRC_MISC:.c=.o))

CC	= gcc
FLG = -Werror -Wextra -Wall
SDL_PATH = sdl2/
SDL2 = `$(SDL_PATH)/sdl2-config --cflags --libs`

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

$(NAME): $(OBJ_SRC) $(OBJ_SDL) $(OBJ_PARSING) $(OBJ_LST) $(OBJ_DATA) $(OBJ_RT) $(OBJ_MISC)
	@if [ ! -d "$(SDL_PATH)lib" ]; then \
		/bin/mkdir $(SDL_PATH)lib; \
		cd $(SDL_PATH) ; ./configure --prefix=`pwd`/lib; \
	fi
	@make -C $(SDL_PATH)
	@make -C $(SDL_PATH) install >/dev/null
	@$(ECHO) "$(C_CYAN)SDL2 compilation done.$(C_NONE)"
	@make -C $(LIB_PATH)
	@make -C $(LIBMATH_PATH)
	@$(CC) $(FLG) $(SDL2) -g $(LIB_PATH)$(LIBFT_NAME) $(LIBMATH_PATH)$(LIBMATHFT_NAME) $(OBJ_PARSING) $(OBJ_SRC) $(OBJ_SDL) $(OBJ_LST) $(OBJ_DATA) $(OBJ_RT) $(OBJ_MISC) -o $(NAME)
	@$(ECHO) "$(C_GREEN)RTv1 compilation done.$(C_NONE)"

$(OBJ_DIR)/%.o : ./src/%.c
	@/bin/mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -g -I./inc -I./$(SDL_PATH)/include -c -o $@ $<

$(OBJ_DIR)/%.o : ./src/sdl/%.c
	@/bin/mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -g -I./inc -I./$(SDL_PATH)/include -c -o $@ $<

$(OBJ_DIR)/%.o : ./src/parsing/%.c
	@/bin/mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -g -I./inc -I./$(SDL_PATH)/include -c -o $@ $<

$(OBJ_DIR)/%.o : ./src/list/%.c
	@/bin/mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -g -I./inc -I./$(SDL_PATH)/include -c -o $@ $<

$(OBJ_DIR)/%.o : ./src/data_prep/%.c
	@/bin/mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -g -I./inc -I./$(SDL_PATH)/include -c -o $@ $<

$(OBJ_DIR)/%.o : ./src/ray_tracing/%.c
	@/bin/mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -g -I./inc -I./$(SDL_PATH)/include -c -o $@ $<

$(OBJ_DIR)/%.o : ./src/misc/%.c
	@/bin/mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -g -I./inc -I./$(SDL_PATH)/include -c -o $@ $<

clean:
	@/bin/rm -Rf $(OBJ_DIR)
	@/bin/rm -Rf $(SDL_PATH)lib
	@/bin/rm -Rf $(SDL_PATH)build
	@$(ECHO) "$(C_CYAN)SDL2 clean done.$(C_NONE)"
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
