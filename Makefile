NAME = cub3D
CC = cc

CCFLAGS = -Wall -Wextra -Werror -g3
MLXFLAGS = -Lmlx_Linux -lmlx_Linux -L ./minilibx-linux -Imlx_Linux -L ./libft -lft -lXext -lX11 -lm -lz

GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[0;34m
BLUE_BOLD = \033[1;34m
PURPLE = \033[1;35m
WHITE = \033[0m

LIBFT = libft/libft.a
MINILIBX = minilibx-linux/libmlx_Linux.a

HEADER_DIR = include/
SOURCES_DIR = sources/
OBJECTS_DIR = objects/

FILENAMES = main/main cleanup/free init/init init/utils \
			parsing/additional parsing/allocate_map parsing/element_parsing \
			parsing/element_parsing_utils parsing/parsing_checks \
			parsing/parsing_utils parsing/parsing parsing/prints parsing/dfs \
			raycaster/utils raycaster/draw raycaster/render

SOURCES = $(addsuffix .c, $(addprefix $(SOURCES_DIR), $(FILENAMES)))
OBJECTS = $(addsuffix .o, $(addprefix $(OBJECTS_DIR), $(FILENAMES)))

all: $(NAME)

$(NAME): $(LIBFT) $(MINILIBX) $(OBJECTS) Makefile
	@echo "$(YELLOW)Compiling $@...$(WHITE)🛠️"
	@$(CC) $(CCFLAGS) -I$(HEADER_DIR) $(LIBFT) $(OBJECTS) -o $(NAME) $(MLXFLAGS)
	@echo "$(GREEN)Done!$(WHITE)✅️"
	@clear
	@echo "$(GREEN)"'                __       ' "$(BLUE_BOLD)" '   __    ____      ' "$(WHITE)"
	@echo "$(GREEN)"'               /\ \     ' "$(BLUE_BOLD)" '  / __ \/\  __ \    ' "$(WHITE)"
	@echo "$(GREEN)"'  ___    __  __\ \ \____ ' "$(BLUE_BOLD)" '/\_\ \ \ \\ \/\ \  ' "$(WHITE)"
	@echo "$(GREEN)"' / ___\ /\\ \/\ \\\ \  __ \' "$(BLUE_BOLD)" '\/_/_\ <\ \ \ \ \  ' "$(WHITE)"
	@echo "$(GREEN)"'/\ \__/\\\ \ \_\ \\\ \ \_\ \' "$(BLUE_BOLD)" ' /\ \_\ \\ \ \_\ \' "$(WHITE)"
	@echo "$(GREEN)"'\ \____/ \ \____/ \ \____/' "$(BLUE_BOLD)" ' \ \____/\ \____/' "$(WHITE)"
	@echo "$(GREEN)"' \/___/   \/___/   \/___/' "$(BLUE_BOLD)" '   \/___/  \/___/ ' "$(WHITE)"
	@echo -n "$(YELLOW)"
	@echo " _                                                       _                              _       "
	@echo "| |_ _ _    ___ ___ ___ ___ ___ ___ ___ _ _    ___ ___ _| |   ___ ___ _____ ___ ___ ___| |_ ___ "
	@echo "| . | | |  |   | .'|_ -| .'|  _| . |_ -| | |  | .'|   | . |  | .'|  _|     | .'|  _| .'| '_| -_|"
	@echo "|___|_  |  |_|_|__,|___|__,|_| |_  |___|_  |  |__,|_|_|___|  |__,|_| |_|_|_|__,|_| |__,|_,_|___|"
	@echo "    |___|                      |___|   |___|                                                    "
	@echo "$(WHITE)"

$(LIBFT):
	@echo "$(BLUE)Compiling $@...$(WHITE)🔨"
	@make bonus -sC libft
	@echo "$(GREEN)Done!$(WHITE)✔︎"

$(MINILIBX):
	@echo "$(BLUE)Compiling $@...$(WHITE)🔨"
	@make -sC minilibx-linux > /dev/null 2> /dev/null
	@echo "$(GREEN)Done!$(WHITE)✔︎"

$(OBJECTS_DIR)%.o: $(SOURCES_DIR)%.c
	@mkdir -p $(dir $@)
	@echo "$(BLUE)Compiling $@...$(WHITE)🔧"
	@$(CC) -c $(CCFLAGS) -I$(HEADER_DIR) -Iminilibx-linux $< -o $@

clean:
	@echo "$(BLUE)Cleaning cub3D object files...$(WHITE)🚮"
	@rm -rf $(OBJECTS_DIR)
	@echo "$(GREEN)Done!$(WHITE)✔︎"
	@echo "$(BLUE)Cleaning libft object files...$(WHITE)🚮"
	@make -sC libft clean
	@echo "$(GREEN)Done!$(WHITE)✔︎"
	@echo "$(BLUE)Cleaning minilibx...$(WHITE)🚮"
	@make -sC minilibx-linux clean > /dev/null 2> /dev/null
	@echo "$(GREEN)Done!$(WHITE)✔︎"

fclean: clean
	@echo "$(BLUE)Deleting $(LIBFT)...$(WHITE)🚮"
	@make -sC libft fclean
	@echo "$(GREEN)Done!$(WHITE)✔︎"
	@echo "$(BLUE)Deleting $(NAME)...$(WHITE)🚮"
	@rm -f $(NAME)
	@echo "$(GREEN)Done!$(WHITE)✅️"

re: fclean all

.PHONY: all clean fclean re
