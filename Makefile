NAME := cub3d
.DEFAULT_GOAL := all
CPP := cc
RM := rm -rf

OBJ_DIR := _obj
INC_DIRS := Includes
SRC_DIRS := src

vpath %.h $(INC_DIRS)
vpath %.c $(SRC_DIRS)

MAIN_FILE := main.c

SRC_FREE_FILES := free.c
SRC_FREE := $(addprefix free/, $(SRC_FREE_FILES))

SRC_PARSING_FILES := parsing.c parsing_utils.c parse_metadata.c parse_map.c assign_colors.c
SRC_PARSING := $(addprefix parsing/, $(SRC_PARSING_FILES))

SRC_INIT_FILES := initialize.c initialize_utils.c
SRC_INIT := $(addprefix initialize/, $(SRC_INIT_FILES))

SRC_RAYCASTING_FILES := dda.c draw_utils.c ray_casting.c ray_init.c rays_utils.c texture_placement.c
SRC_RAYCASTING := $(addprefix raycasting/, $(SRC_RAYCASTING_FILES))

SRC_MOVEMENT_FILES := key_handle.c move.c
SRC_MOVEMENT := $(addprefix movement/, $(SRC_MOVEMENT_FILES))

SRCS := $(MAIN_FILE) $(addprefix src/, $(SRC) $(SRC_PARSING) $(SRC_INIT) $(SRC_RAYCASTING) $(SRC_MOVEMENT) $(SRC_FREE))

OBJS := $(addprefix $(OBJ_DIR)/, $(SRCS:%.c=%.o))

# Base CFLAGS - Add -MMD -MP for dependency generation
BASE_CFLAGS := -Wall -Werror -Wextra -O3 -MMD -MP $(addprefix -I, $(INC_DIRS))
CFLAGS := $(BASE_CFLAGS)

# Base LDFLAGS
BASE_LDFLAGS := -lncurses # Keep if ncurses is actually used, otherwise remove

# --- OS Detection ---
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Darwin) # macOS
	MLX_LIB_PATH := ./MLX42/build/libmlx42.a
	# Assuming glfw installed via Homebrew and findable by linker, or MLX42 handles it.
	# If linker fails to find glfw, you might need: -L/path/to/glfw/lib
	MLXFLAGS := -framework Cocoa -framework OpenGL -framework IOKit -lglfw
	# Add MLX lib path and lib itself
	LDFLAGS := $(BASE_LDFLAGS) -L./MLX42/build -lmlx42 $(MLXFLAGS)
	LDFLAGS_SAN := $(LDFLAGS) -fsanitize=address
	CFLAGS_SAN := $(BASE_CFLAGS) -fsanitize=address
else ifeq ($(UNAME_S), Linux) # Linux
	MLX_LIB_PATH := ./MLX42/build/libmlx42.a
	# Basic Linux libs for OpenGL/GLFW/X11. Adjust if needed.
	MLXFLAGS := -lglfw -lGL -lX11 -lpthread -lm -ldl
	# Add MLX lib path and lib itself
	LDFLAGS := $(BASE_LDFLAGS) -L./MLX42/build -lmlx42 $(MLXFLAGS)
	LDFLAGS_SAN := $(LDFLAGS) -fsanitize=address
	CFLAGS_SAN := $(BASE_CFLAGS) -fsanitize=address
else
	$(error Unsupported OS: $(UNAME_S))
endif
# --- End OS Detection ---

GREEN := \033[0;32m
MAGENTA := \033[0;35m
RED := \033[0;31m
BOLD := \033[1m
NC := \033[0m

all: linux_requirements mlx_42 art lib $(NAME)

$(NAME): $(OBJS) lib $(MLX_LIB_PATH)
	@echo "Linking $(NAME) with flags: $(LDFLAGS)"
	$(CPP) $(OBJS) ./lib/lib.a $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)$(BOLD)Successful Compilation on $(UNAME_S)$(NC)"

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(@D)
	@echo "Compiling $<"
	$(CPP) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Target to ensure MLX library exists before linking main executable
$(MLX_LIB_PATH): mlx_42
	@echo "MLX42 library built."

linux_requirements:
ifeq ($(UNAME_S), Linux)
	@echo "Running Linux requirements script..."
	bash linux_requirements.sh
	@echo "Linux requirements script completed."
endif

mlx_42:
	@echo "Building MLX42 submodule..."
	@git submodule update --init --remote --recursive
	@(cd MLX42 && cmake -B build && cmake --build build -j4)

lib:
	@echo "Building lib submodule..."
	@$(MAKE) -C lib

clean:
	@echo "Cleaning project objects..."
	$(RM) $(OBJ_DIR)
	@echo "Cleaning lib submodule..."
	@$(MAKE) -C lib clean || true
	@echo "Cleaning MLX42 build..."
	@$(RM) -r ./MLX42/build || true

fclean: clean
	@echo "Cleaning executable $(NAME)..."
	$(RM) $(NAME)
	@echo "Cleaning lib submodule (fclean)..."
	@$(MAKE) -C lib fclean || true
	# No need to fclean MLX42 typically, build dir removal in clean is enough
	@echo "$(MAGENTA)$(BOLD)Executable + Object Files + Submodule libs cleaned$(NC)"

re: fclean all

submodule_update:
	git submodule update --remote --merge

# --- Help Target ---
help: art
	@echo ""
	@echo "$(BOLD)$(CYAN) Cub3d Makefile Help $(NC)"
	@echo "$(CYAN)--------------------------------------------------------------------$(NC)"
	@echo " Usage: $(BOLD)make $(YELLOW)[target]$(NC)"
	@echo ""
	@echo " $(GREEN)🛠️  Core Build Targets:$(NC)"
	@printf "   $(BOLD)%-20s$(NC) : %s\n" "all" "Build the '$(NAME)' executable (default goal)."
	@echo ""
	@echo " $(RED)🧹 Cleaning Targets:$(NC)"
	@printf "   $(BOLD)%-20s$(NC) : %s\n" "clean" "Remove object files ($(OBJ_DIR)) and submodule temp files."
	@printf "   $(BOLD)%-20s$(NC) : %s\n" "fclean" "Remove object files, the executable '$(NAME)', and submodule libraries."
	@printf "   $(BOLD)%-20s$(NC) : %s\n" "re" "Perform 'fclean' then 'all' (full rebuild)."
	@echo ""
	@echo " $(YELLOW)🔍 Debugging & Analysis:$(NC)"
	@printf "   $(BOLD)%-20s$(NC) : %s\n" "san" "Rebuild with AddressSanitizer for memory error detection."
	@printf "   $(BOLD)%-20s$(NC) : %s\n" "debug" "Rebuild with extra debug flags enabled (-DDEBUG)."
	@printf "   $(BOLD)%-20s$(NC) : %s\n" "valgrind" "Run 're' then execute '$(NAME)' under Valgrind."
	@printf "   $(BOLD)%-20s$(NC) : %s\n" "cppcheck" "Run 're' then perform static code analysis with cppcheck."
	@echo ""
	@echo " $(BLUE)🧩 Submodule Management:$(NC)"
	@printf "   $(BOLD)%-20s$(NC) : %s\n" "mlx_42" "Build the MLX42 library submodule (usually automatic)."
	@printf "   $(BOLD)%-20s$(NC) : %s\n" "lib" "Build the 'lib' submodule (usually automatic)."
	@printf "   $(BOLD)%-20s$(NC) : %s\n" "submodule_update" "Update submodules to their latest remote commits."
	@printf "   $(BOLD)%-20s$(NC) : %s\n" "re_sub" "Forcefully reinitialize submodules (if update/build fails)."
	@echo ""
	@echo " $(MAGENTA)✨ Other Targets:$(NC)"
	@printf "   $(BOLD)%-20s$(NC) : %s\n" "linux_requirements" "Install required packages on Linux (automatic on 'all')."
	@printf "   $(BOLD)%-20s$(NC) : %s\n" "art" "Display cool ASCII art (automatic on 'all')."
	@echo "$(CYAN)--------------------------------------------------------------------$(NC)"
	@echo ""

# Note: The san target re-runs make with different flags
san: fclean
	@echo "$(MAGENTA)Recompiling with Address Sanitizer...$(NC)"
	$(MAKE) CFLAGS="$(CFLAGS_SAN)" LDFLAGS="$(LDFLAGS_SAN)" all
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
	valgrind --leak-check=full --show-leak-kinds=definite --track-origins=yes ./$(NAME) ./maps/map2.cub

cppcheck: re
	cppcheck --enable=warning,style,performance,portability --enable=unusedFunction $(SRCS)


debug: clean
debug: CFLAGS += -DDEBUG
debug: $(NAME)

# Include dependency files
-include $(OBJS:%.o=%.d)

.PHONY: all art clean fclean re re_sub submodule_rebuild san debug lib mlx_42 submodule_update valgrind cppcheck help