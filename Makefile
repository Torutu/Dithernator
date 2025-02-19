# Target Names
NAME_LINUX = linux_dithernator
NAME_WINDOWS = win_dithernator.exe

# Compilers
CC_LINUX = c++
CC_WINDOWS = x86_64-w64-mingw32-g++

# Compiler Flags
CFLAGS = -Wall -Wextra -w -std=c++17 -I./inc
LDFLAGS_LINUX = -lstdc++
LDFLAGS_WINDOWS = -static -static-libgcc -static-libstdc++ -lstdc++ -lm -lmingw32 -lgcc

# Source Files
SRC = src/main.cpp src/minunDither.cpp
OBJ_DIR_LINUX = obj_linux
OBJ_DIR_WINDOWS = obj_win
OBJ_LINUX = $(SRC:src/%.cpp=$(OBJ_DIR_LINUX)/%.o)
OBJ_WINDOWS = $(SRC:src/%.cpp=$(OBJ_DIR_WINDOWS)/%.o)

# Color codes
RED = \033[31m
GREEN = \033[32m
MAGENTA = \033[35m
RESET = \033[0m

SHELL := /bin/bash

all: linux

linux: $(NAME_LINUX)

windows: $(NAME_WINDOWS)

# Create the object directories
$(OBJ_DIR_LINUX):
	@ mkdir -p $(OBJ_DIR_LINUX)

$(OBJ_DIR_WINDOWS):
	@ mkdir -p $(OBJ_DIR_WINDOWS)

$(NAME_LINUX): $(OBJ_DIR_LINUX) $(OBJ_LINUX)
	@ echo -ne "$(MAGENTA)Making $(NAME_LINUX)"
	@ ( \
		trap 'echo -e "$(RED)Interrupted by user $(RESET)"; exit 1' INT; \
		$(CC_LINUX) $(CFLAGS) -o $(NAME_LINUX) $(OBJ_LINUX) $(LDFLAGS_LINUX) & \
		PID=$$!; \
		while kill -0 $$PID 2>/dev/null; do \
			echo -n "."; \
			sleep 0.4; \
			echo -n "."; \
			sleep 0.6; \
			echo -n "."; \
			sleep 0.4; \
		done; \
		wait $$PID; \
	)
	@ echo -ne "\n$(GREEN)Done!$(RED)\n"

$(NAME_WINDOWS): $(OBJ_DIR_WINDOWS) $(OBJ_WINDOWS)
	@ echo -ne "$(MAGENTA)Making $(NAME_WINDOWS)"
	@ ( \
		trap 'echo -e "$(RED)Interrupted by user $(RESET)"; exit 1' INT; \
		$(CC_WINDOWS) $(CFLAGS) -o $(NAME_WINDOWS) $(OBJ_WINDOWS) $(LDFLAGS_WINDOWS) & \
		PID=$$!; \
		while kill -0 $$PID 2>/dev/null; do \
			echo -n "."; \
			sleep 0.4; \
			echo -n "."; \
			sleep 0.6; \
			echo -n "."; \
			sleep 0.4; \
		done; \
		wait $$PID; \
	)
	@ echo -ne "\n$(GREEN)Done!$(RED)\n"

# Separate compilation rules for Linux and Windows

$(OBJ_DIR_LINUX)/%.o: src/%.cpp
	@ $(CC_LINUX) $(CFLAGS) -D_NDEBUG -c $< -o $(OBJ_DIR_LINUX)/$(@F)

$(OBJ_DIR_WINDOWS)/%.o: src/%.cpp
	@ $(CC_WINDOWS) $(CFLAGS) -D_NDEBUG -c $< -o $(OBJ_DIR_WINDOWS)/$(@F)

clean:
	@ echo -e "$(RED)Removing $(OBJ_DIR_LINUX)$(RESET)"
	@ rm -rf $(OBJ_DIR_LINUX)
	@ echo -e "$(RED)Removing $(OBJ_DIR_WINDOWS)$(RESET)"
	@ rm -rf $(OBJ_DIR_WINDOWS)

fclean: clean
	@ echo -e "$(RED)Removing binaries$(RESET)"
	@ rm -f $(NAME_LINUX) $(NAME_WINDOWS)

re: fclean all

.PHONY: all linux windows clean fclean re
