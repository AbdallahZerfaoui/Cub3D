NAME := cub3d
.DEFAULT_GOAL := all
CPP := cc
AR := ar
RM := rm -rf

OBJ_DIR := _obj
INC_DIRS := Includes
SRC_DIRS := src src/subrepo

vpath %.h $(INC_DIRS)
vpath %.c $(SRC_DIRS)

MAIN_FILE := main.c

SRC_FREE_FILES := free.c
SRC_FREE := $(addprefix free/, $(SRC_FREE_FILES))

SRC_PARSING_FILES := parsing.c parsing_utils.c parse_metadata.c parse_map.c
SRC_PARSING := $(addprefix parsing/, $(SRC_PARSING_FILES))

SRC_INIT_FILES := initialize.c initialize_utils.c
SRC_INIT := $(addprefix initialize/, $(SRC_INIT_FILES))

SRC_RAYCASTING_FILES := draw_rays.c rays_utils.c
SRC_RAYCASTING := $(addprefix raycasting/, $(SRC_RAYCASTING_FILES))

SRC_MOVEMENT_FILES := key_handle.c move.c
SRC_MOVEMENT := $(addprefix movement/, $(SRC_MOVEMENT_FILES))

SRC := 
SRCS := $(MAIN_FILE) $(addprefix src/, $(SRC) $(SRC_PARSING) $(SRC_INIT) $(SRC_RAYCASTING) $(SRC_MOVEMENT) $(SRC_FREE))

OBJS := $(addprefix $(OBJ_DIR)/, $(SRCS:%.c=%.o))

# CFLAGS := -Wall -Werror -Wextra -Wconversion -Wsign-conversion -g -MMD -MP $(addprefix -I, $(INC_DIRS))
CFLAGS := -Wall -Werror -Wextra $(addprefix -I, $(INC_DIRS))
USER = $(shell whoami)
MLXFLAGS := -framework Cocoa -framework OpenGL -framework IOKit -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"
CFLAGS_SAN := $(CFLAGS) -fsanitize=address
LDFLAGS := -lncurses
LDFLAGS_SAN := -lncurses -fsanitize=address
ARFLAGS := -rcs

GREEN := \033[0;32m
MAGENTA := \033[0;35m
RED := \033[0;31m
BOLD := \033[1m
NC := \033[0m

all: mlx_42 art lib $(NAME)

$(NAME): $(OBJS) lib
	$(CPP) $(LDFLAGS) $(OBJS) -o $(NAME) ./lib/lib.a ./MLX42/build/libmlx42.a $(MLXFLAGS)
	@echo "$(GREEN)$(BOLD)Successful Compilation$(NC)"

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	mkdir -p $(@D)
	$(CPP) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

mlx_42:
	git submodule update --init --remote --recursive
	(cd MLX42 && cmake -B build && cmake --build build -j4)

lib:
	@$(MAKE) -C lib

clean:
	$(RM) $(OBJ_DIR)
	@$(MAKE) -C lib clean || true

fclean: clean
	$(RM) $(NAME)
	@$(MAKE) -C lib fclean || true
	@echo "$(MAGENTA)$(BOLD)Executable + Object Files cleaned$(NC)"

# re: fclean submodule_update all
re: fclean all

submodule_update:
	git submodule update --remote --merge

bonus: all

san: fclean
	make CFLAGS="$(CFLAGS_SAN)" LDFLAGS="$(LDFLAGS_SAN)"
	@echo "$(GREEN)$(BOLD)Successful Compilation with fsan$(NC)"

re_sub: submodule_rebuild

submodule_rebuild:
	git submodule deinit -f .
	git submodule update --init --recursive

art: 
	@echo "${GREEN}                    __       _____    ____  "
	@echo "  _____   __  __   / /_     |__  /   / __ \\ "
	@echo " / ___/  / / / /  / __ \     /_ <   / / / / ${NC}"
	@echo "${RED}/ /__   / /_/ /  / /_/ /   ___/ /  / /_/ /  "
	@echo "\___/   \__,_/  /_.___/   /____/  /_____/   "
	@echo "                                            ${NC}"

valgrind: re
	valgrind --leak-check=full --show-leak-kinds=definite --track-origins=yes ./$(NAME) ./maps/map.cub

cppcheck: re
	cppcheck --enable=warning,style,performance,portability --enable=unusedFunction $(SRCS)


debug: clean
debug: CFLAGS += -DDEBUG
debug: $(NAME)


-include $(OBJS:%.o=%.d)

.PHONY: all art clean fclean re bonus re_sub submodule_rebuild san debug lib
