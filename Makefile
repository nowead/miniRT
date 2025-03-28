NAME			=	miniRT

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror -O3
RM = rm -f

INCLUDES		=	$(addprefix includes/, minirt.h)
PARSE_DIR		=	parse/
RENDER_DIR		=	render/
SRC				=	$(addprefix sources/, minirt.c setup_event_hooks.c my_mlx_functions.c	manipulate_camera.c	manipulate_object.c\
					manipulate_light.c\
$(addprefix $(PARSE_DIR),	parse_scene.c		parse_utils.c			parse_object.c		parse_object_cap.c	parse_light.c\
							parse_types.c		parse_error_check.c	parse_scene_element.c	parse_texture.c)\
$(addprefix $(RENDER_DIR),	compute_lighting.c	intersect_ray_plane.c	render_scene.c		vector_operations1.c\
						   	vector_operations2.c	intersect_ray_cylinder.c	intersect_ray_cone.c	get_normal_vector.c\
							closest_intersection.c		intersect_ray_sphere.c	compute_circle_intersection.c\
							get_surface_color.c		apply_bump_map.c	convert_to_texture_space.c))
OBJ				=	$(patsubst %.c, %.o, $(SRC))

MLX				=	libmlx.dylib
# MLX				=	libmlx.a
MLX_DIR			=	mlx/
MLX_HEADER		=	$(MLX_DIR)mlx.h
MLX_FLAGS		=	-Lmlx -lmlx -framework OpenGL -framework AppKit

LIBFT 			=	$(LIBFT_DIR)libft.a
LIBFT_DIR		=	libft/
LIBFT_SRC		=	$(addprefix $(LIBFT_DIR), \
ft_isalpha.c    ft_memchr.c     ft_putchar_fd.c ft_strchr.c     ft_strlcpy.c    ft_strrchr.c	ft_atoi.c\
ft_atol.c		ft_isascii.c    ft_isspace.c	ft_memcmp.c     ft_putendl_fd.c ft_strdup.c     ft_strlen.c\
ft_strtrim.c	ft_bzero.c      ft_isdigit.c    ft_memcpy.c     ft_putnbr_fd.c  ft_striteri.c   ft_strmapi.c\
ft_substr.c		ft_calloc.c     ft_isprint.c    ft_memmove.c    ft_putstr_fd.c  ft_strjoin.c    ft_strncmp.c\
ft_tolower.c	ft_isalnum.c    ft_itoa.c       ft_memset.c     ft_split.c      ft_strlcat.c    ft_strnstr.c\
ft_toupper.c	ft_strlncpy.c	ft_strlncat.c	ft_strtol.c		ft_strtol1.c\
get_next_line.c					get_next_line_utils.c)
LIBFT_SCENE		=	$(patsubst %.c, %.o, $(LIBFT_SRC))
LIBFT_HEADER	=	$(addprefix $(LIBFT_DIR), libft.h get_next_line.h)
LIBFT_FLAGS		=	-Llibft -lft

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	@$(CC) $(OBJ) $(LIBFT_FLAGS) $(MLX_FLAGS) -o $(NAME)
	@echo "Linked into executable \033[0;32mminiRT\033[0m."

$(MLX): $(MLX_DIR)$(MLX)
	@cp $(MLX_DIR)$(MLX) .

$(MLX_DIR)$(MLX):
	@make -C $(MLX_DIR)

$(LIBFT): $(LIBFT_SRC) $(LIBFT_HEADER)
	@make -C $(LIBFT_DIR)

%.o: %.c $(INCLUDES) $(MLX_HEADER) $(LIBFT_HEADER)
	@$(CC) $(CFLAGS) -Imlx -Ilibft -Iincludes -c $< -o $@

clean:
	@$(RM) $(OBJ)
	@echo "remove \033[0;31mobject files\033[0m"
	@make -C $(LIBFT_DIR) clean
	@echo "\033[0;31mlibft\033[0m clean."
	@make -C $(MLX_DIR) clean
	@echo "\033[0;31mmlx\033[0m clean."

fclean: clean
	@$(RM) $(LIBFT)
	@echo "remove \033[0;31mlibft.a\033[0m."
	@$(RM) libmlx.dylib
	@echo "remove \033[0;31mlibmlx.dylib\033[0m."
	@$(RM) $(NAME)
	@echo "remove \033[0;31mexecutable\033[0m."

re: fclean all

.PHONY: all clean fclean re


# CC = clang
# CFLAGS = -Wall -Wextra -Werror -O3 -Iincludes -Imlx -Iopengl
# CLIB   = -Lmlx -lmlx -framework OpenGL -framework Appkit -Imlx

# NAME = miniRT

# SRCSDIR = sources/
# MLX_HOOK_DIR = mlx_hook/
# MLX_DRAW_DIR = mlx_draw/
# MLXDIR = mlx/
# OPENGLDIR = opengl/
# LIBFTDIR = libft/
# SUBDIRS = mlx opengl libft

# INCLDS = includes

# MLX_HOOK_SRCS = $(addprefix $(MLX_HOOK_DIR), handle_hook.c)
# MLX_DRAW_SRCS = $(addprefix $(MLX_DRAW_DIR), draw.c)
# SRCS = $(addprefix $(SRCSDIR), main.c $(MLX_DRAW_SRCS) $(MLX_HOOK_SRCS))
# OBJS = $(SRCS:.c=.o)

# MLXLIB = $(addprefix $(MLXDIR), libmlx.dylib)
# OPENGLLIB = $(addprefix $(OPENGLDIR), libmlx.a)
# LIBFTLIB = $(addprefix $(LIBFTDIR), libft.a)
# SUBLIBS = $(MLXLIB) $(OPENGLLIB) $(LIBFTLIB)

# OBJECTS = $(OBJS) $(SUBLIBS)
# HEADERS = 
# DEPENDENCY = $(HEADERS) $(LIBFTLIB) $(MLXLIB) $(OPENGLLIB)

# AR = ar
# ARFLAGS = rcs
# RM = rm -f

# all: $(NAME)

# $(NAME): $(OBJECTS)
# 	$(CC) $(CLIB) $^ -o $(NAME)
# 	install_name_tool -change libmlx.dylib mlx/libmlx.dylib $(NAME)
# 	@echo "Linked into executable \033[0;32mminiRT\033[0m."

# %.o: %.c
# 	$(CC) $(CFLAGS) -c $< -o $@
	
# $(SUBLIBS):
# 	@for dir in $(SUBDIRS); do $(MAKE) -C $$dir; done

# clean:
# 	@$(RM) $(OBJS)
# 	@echo "remove \033[0;31mobject files\033[0m"
# ifeq (1, $(shell test -e libft/libft.a && echo 1))
# 	@$(MAKE) -s -C $(LIBFTDIR) clean	
# 	@echo "\033[0;31mlibft\033[0m clean."
# endif
# ifeq (1, $(shell test -e mlx/libmlx.dylib && echo 1))
# 	@$(MAKE) -s -C $(MLXDIR) clean	
# 	@echo "\033[0;31mmlx\033[0m clean."
# endif
# ifeq (1, $(shell test -e opengl/libmlx.a && echo 1))
# 	@$(MAKE) -s -C $(OPENGLDIR) clean	
# 	@echo "\033[0;31mopengl\033[0m clean."
# endif
	
# fclean: clean
# 	@$(RM) $(LIBFTLIB)
# 	@echo "remove \033[0;31mlibft.a\033[0m."
# 	@$(RM) libmlx.dylib
# 	@echo "remove \033[0;31mlibmlx.dylib\033[0m."
# 	@$(RM) $(NAME)
# 	@echo "remove \033[0;31mexecutable\033[0m."

# re: 
# 	make fclean
# 	make all

# .PHONY: all clean bonus fclean re