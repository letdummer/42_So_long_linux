# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldummer- <ldummer-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/21 17:06:37 by ldummer-          #+#    #+#              #
#    Updated: 2025/06/17 17:26:15 by ldummer-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME= so_long

#------------------------------------------------------------------------------#
#									FILES  				     				   #
#------------------------------------------------------------------------------#

SRC_DIR		= src
OBJ_DIR		= .build
INCLUDES	= includes
HEADERS = $(INCLUDES)/so_long.h

SRC_FILES	=	cleaning.c			\
				flood_fill.c		\
				init_map.c			\
				init_window.c		\
				movements.c			\
				render_images.c		\
				so_long.c			\
				update_images.c		\
				validate_map.c		\
				validate_map_path.c		\
				
SRC			= $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ			= $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

#	Librarys
LIBFT_DIR	= libft
LIBFT_LIB	= $(LIBFT_DIR)/libft.a

MLX_DIR		= minilibx-linux
MLX			= $(MLX_DIR)/libmlx.a
MLXFLAGS	= -L$(MLX_DIR) -lmlx -lXext -lX11

#------------------------------------------------------------------------------#
#								COMPILATION 		  						   #
#------------------------------------------------------------------------------#

CC		= cc
CFLAGS	= -g -Wall -Wextra -Werror
DFLAGS	= -g
RM= rm -f

ifeq ($(UNAME_S),Linux)
	CFLAGS += -I/usr/include/X11
	MLXFLAGS += -L. -lXext -L. -lX11
endif

ifeq ($(UNAME_S),Darwin)
	MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
	CFLAGS += -I$(MLX_DIR)
endif

#------------------------------------------------------------------------------#
#								BASE		 		  						   #
#------------------------------------------------------------------------------#

all: deps $(NAME) 

$(NAME): $(MLX) $(OBJ) $(LIBFT_LIB)
	@$(CC) $(CFLAGS) -I$(INCLUDES) $(OBJ) -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lXext -lX11 -o $(NAME)
	$(call success, "Build complete: $(NAME) 📚 ✨")

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@mkdir -p $(OBJ_DIR)
	$(call warn, "Compiling [...] $<")
	@$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@

$(LIBFT_LIB) :
	@if [ ! -f "$(LIBFT_LIB)" ]; then \
		$(MAKE) -C $(LIBFT_DIR) all bonus extra --silent; \
	fi

$(MLX):
	@if [ ! -d "$(MLX_DIR)" ]; then \
		echo "Getting minilibx for Linux"; \
		curl -O https://cdn.intra.42.fr/document/document/32345/minilibx-linux.tgz && \
		tar -xzf minilibx-linux.tgz && \
		rm -f minilibx-linux.tgz; \
	fi
	@if [ ! -f "$(MLX)" ]; then \
		$(MAKE) -C $(MLX_DIR); \
	fi

deps: get_libft
	@if [ -d "$(LIBFT_DIR)" ]; then \
		$(MAKE) -C $(LIBFT_DIR) all bonus extra --silent > /dev/null; \
		echo "[$(GREEN_BOLD)All deps installed!$(RESET)]"; \
	else \
		echo "Error: Libft directory not found after attempting to download"; \
		exit 1; \
	fi

get_libft:
	@if [ ! -d "$(LIBFT_DIR)" ]; then \
		echo "Getting Libft"; \
		git clone --depth 1 https://github.com/letdummer/42_libft.git $(LIBFT_DIR); \
		echo "Done downloading Libft"; \
	else \
		echo "Libft directory already exists"; \
	fi


#------------------------------------------------------------------------------#
#								CLEAN-UP RULES 		  						   #
#------------------------------------------------------------------------------#
#	clean the .o objects
clean:
	$(call text, "Removing object files [...]")
	@$(RM) $(OBJ)
	@make -C $(LIBFT_DIR) clean --silent
	$(call success, "		Object files cleaned. 💣"); \

# clean the .o objects, the objs folder and the project file
fclean: clean
	$(call text, "Removing files [...]")
	@$(RM) $(NAME)
	@$(MAKE) --silent -C $(LIBFT_DIR) fclean
	$(call highligth_bold, "FULL CLEANING DONE! ✅")

#	refresh the project
re: fclean all
	$(call success, "All files have been recompiled ✅")

#------------------------------------------------------------------------------#
#								EXTRA		 		  						   #
#------------------------------------------------------------------------------#
#________		GDB					___________________________________________#
#	Run with GDB w/ custom arg=""
gdb:				
	gdb --tui --args ./$(NAME) $(INPUT)


#________		VALGRIND			___________________________________________#
#	rule to valgrind
valgrind: $(NAME)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFTLIB) -o $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) $(INPUT)
	make clean
	./so_long $(INPUT)

	
#------------------------------------------------------------------------------#
#								HELP MENU	 		  						   #
#------------------------------------------------------------------------------#

help:
	@echo "$(CYAN_BOLD)\n\tAVAILABLE OPTIONS:$(RESET)"
	@echo "$(CYAN_BOLD)\t---------------------------------$(RESET)"
	@echo "$(CYAN)\tmake			- Compiles the project. $(NAME).$(RESET)"
	@echo "$(CYAN)\tmake clean		- Removes object files (.o).$(RESET)"
	@echo "$(CYAN)\tmake fclean	  	- Removes object files and the library $(NAME).$(RESET)"
	@echo "$(CYAN)\tmake re			- Cleans and recompiles the project.$(RESET)"
	@echo "$(CYAN)\tmake valgrind	- To run valgrind with "--leak-check=full".$(RESET)"
	@echo "$(CYAN)\tmake help		- Displays this help message.$(RESET)"
#	@echo "$(CYAN)\tmake manual		- Displays the push_swap manual.$(RESET)"

#------------------------------------------------------------------------------#
#						COLORS AND WARNINGS		 	 						   #
#------------------------------------------------------------------------------#
# font name for titles: ANSI REGULAR
# https://patorjk.com/software/taag/#p=display&f=ANSI%20Regular&t=push_swap

# or https://www.asciiart.eu/text-to-ascii-art
# Alligator width 80

#________		DEFINING ANSI COLORS___________________________________________#

RED_BOLD	  := $(shell echo "\033[1;31m")
GREEN_BOLD	:= $(shell echo "\033[1;32m")
PURPLE  := $(shell echo "\033[0;35m")
BLUE	 := $(shell echo "\033[0;34m")
CYAN	:= $(shell echo "\033[0;36m")
CYAN_BOLD	:= $(shell echo "\033[1;36m")
RESET	:= $(shell echo "\033[0m")

#________		FUNCTIONS TO PRINT COLORS______________________________________#

text = @echo "$(PURPLE)$(1)$(RESET)"
warn = @echo "$(BLUE)$(1)$(RESET)"
error = @echo "$(RED_BOLD)$(1)$(RESET)"
success = @echo "$(GREEN_BOLD)$(1)$(RESET)"
highligth = @echo "$(CYAN)$(1)$(RESET)"
highligth_bold = @echo "$(CYAN_BOLD)$(1)$(RESET)"


#______________________________________________________________________________#
.PHONY: all clean fclean re help manual valgrind gdb deps libft

libft: $(LIBFT_LIB)

deps: get_libft libft