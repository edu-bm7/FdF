# C Compiler (Clang-12)
CC := cc
# FdF Variables
NAME := fdf
INC_DIR := includes/
OBJS_DIR := objects/
SRC_DIR := src/
# Libft Variables
LIB_INC_DIR := libft/
LIBFT_DIR := libft/
LIBFT := libft.a
# Maps for testing FdF
MAPS_FILE := maps.zip
MAPS_FOLDER := test_maps

CFLAGS = -Wall -Wextra -Werror -I$(LIB_INC_DIR) -I$(INC_DIR)

SRCS = $(addprefix $(SRC_DIR), main.c\
		utils.c\
		init/map_init.c\
		mlx/mlx.c\
		map_validation/find_min_max.c\
		map_validation/validate_map.c\
		draw_map/draw.c\
		draw_map/map_transformation.c\
		bresenham/bresenham.c\
		bresenham/bresenham_utils.c\
		)

OBJS = $(patsubst $(SRC_DIR)%.c, $(OBJS_DIR)%.o, $(SRCS))
# All Src subdirectories
SRC_SUBDIR := $(shell find $(SRC_DIR) -type d)
# Objects Subdirectories
OBJS_SUBDIR := $(subst $(SRC_DIR), $(OBJS_DIR), $(SRC_SUBDIR))

$(NAME): $(OBJS) | libft
	@$(CC) $(OBJS) -o $@ -lX11 -lm -lXext -lmlx -L$(LIBFT_DIR) -lft
	@echo "--------------------------"
	@echo "FdF binary created."
	@echo "--------------------------"

libft:
	@make -C $(LIBFT_DIR)

$(OBJS_DIR)%.o: $(SRC_DIR)%.c
	@if [ ! -d "$(OBJS_DIR)" ]; then \
		mkdir -p $(OBJS_SUBDIR); \
	fi
	@$(CC) $(CFLAGS) -c $? -o $@

.PHONY: all clean fclean re log libft maps clean_maps

all: $(NAME)

clean:
	@rm -rf $(OBJS_DIR)
	@echo "--------------------------"
	@echo "FdF Objects removed."
	@echo "--------------------------"
	@make clean -C $(LIBFT_DIR)

fclean: clean
	@rm -f $(NAME)
	@echo "FdF removed."
	@echo "--------------------------"
	@make fclean -C $(LIBFT_DIR)

re: fclean all

log:
	@echo "FdF Source Files:" $(SRCS)
	@printf "\n"
	@echo "FdF Objects Files:" $(OBJS)
	@printf "\n"
# Download and unzip the maps for testing FdF
maps:
	@if [ ! -f "$(MAPS_FILE)" ]; then \
		wget --no-hsts https://projects.intra.42.fr/uploads/document/document/9390/maps.zip; \
	fi
	@if [ ! -d "$(MAPS_FOLDER)" ]; then \
			unzip $(MAPS_FILE); \
	fi
	
# Clean the tests maps downloaded
clean_maps:
	@rm -rf $(MAPS_FOLDER) $(MAPS_FILE) __MACOSX
	@echo "--------------------------"
	@echo "Maps removed."
	@echo "--------------------------"
