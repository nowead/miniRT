# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: damin <damin@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/28 21:00:50 by damin             #+#    #+#              #
#    Updated: 2024/08/30 18:37:26 by damin            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang
CFLAGS = -Wall -Wextra -Werror -O3 -Iincludes -Imlx -Iopengl
CLIB   = -Lmlx -lmlx -framework OpenGL -framework Appkit -Imlx

NAME = miniRT

SRCSDIR = sources/
MLX_HOOK_DIR = mlx_hook/
MLX_DRAW_DIR = mlx_draw/
MLXDIR = mlx/
OPENGLDIR = opengl/
LIBFTDIR = libft/
SUBDIRS = mlx opengl libft

INCLDS = includes

MLX_HOOK_SRCS = $(addprefix $(MLX_HOOK_DIR), handle_hook.c)
MLX_DRAW_SRCS = $(addprefix $(MLX_DRAW_DIR), draw.c)
SRCS = $(addprefix $(SRCSDIR), main.c $(MLX_DRAW_SRCS) $(MLX_HOOK_SRCS))
OBJS = $(SRCS:.c=.o)

MLXLIB = $(addprefix $(MLXDIR), libmlx.dylib)
OPENGLLIB = $(addprefix $(OPENGLDIR), libmlx.a)
LIBFTLIB = $(addprefix $(LIBFTDIR), libft.a)
SUBLIBS = $(MLXLIB) $(OPENGLLIB) $(LIBFTLIB)

OBJECTS = $(OBJS) $(SUBLIBS)
HEADERS = 
DEPENDENCY = $(HEADERS) $(LIBFTLIB) $(MLXLIB) $(OPENGLLIB)

AR = ar
ARFLAGS = rcs
RM = rm -f

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CLIB) $^ -o $(NAME)
	install_name_tool -change libmlx.dylib mlx/libmlx.dylib $(NAME)
	@echo "Linked into executable \033[0;32mminiRT\033[0m."

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
	
$(SUBLIBS):
	@for dir in $(SUBDIRS); do $(MAKE) -C $$dir; done

clean:
	@$(RM) $(OBJS)
	@echo "remove \033[0;31mobject files\033[0m"
ifeq (1, $(shell test -e libft/libft.a && echo 1))
	@$(MAKE) -s -C $(LIBFTDIR) clean	
	@echo "\033[0;31mlibft\033[0m clean."
endif
ifeq (1, $(shell test -e mlx/libmlx.dylib && echo 1))
	@$(MAKE) -s -C $(MLXDIR) clean	
	@echo "\033[0;31mmlx\033[0m clean."
endif
ifeq (1, $(shell test -e opengl/libmlx.a && echo 1))
	@$(MAKE) -s -C $(OPENGLDIR) clean	
	@echo "\033[0;31mopengl\033[0m clean."
endif
	
fclean: clean
	@$(RM) $(LIBFTLIB)
	@echo "remove \033[0;31mlibft.a\033[0m."
	@$(RM) libmlx.dylib
	@echo "remove \033[0;31mlibmlx.dylib\033[0m."
	@$(RM) $(NAME)
	@echo "remove \033[0;31mexecutable\033[0m."

re: 
	make fclean
	make all

.PHONY: all clean bonus fclean re 
