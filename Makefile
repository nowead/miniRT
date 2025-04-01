NAME			=	miniRT

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror -O3
RM				=	rm -f

UNAME_S := $(shell uname -s)
ARCH := $(shell uname -m)

# 시스템에 따라 mlx 설정 분기
ifeq ($(ARCH), arm64)  # Apple Silicon
	MLX_DIR		=	mlx_macbook/
	MLX_LIB		=	libmlx.a
	MLX_FLAGS	=	-L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
else  # Intel Mac
	MLX_DIR		=	mlx/
	MLX_LIB		=	libmlx.dylib
	MLX_FLAGS	=	-L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
endif

MLX_HEADER		=	$(MLX_DIR)mlx.h

LIBFT_DIR		=	libft/
LIBFT			=	$(LIBFT_DIR)libft.a
LIBFT_HEADER	=	$(addprefix $(LIBFT_DIR), libft.h get_next_line.h)
LIBFT_FLAGS		=	-L$(LIBFT_DIR) -lft

INCLUDES		=	$(addprefix includes/, minirt.h)

PARSE_DIR		=	sources/parse/
RENDER_DIR		=	sources/render/
SRC				=	\
	$(addprefix sources/, minirt.c setup_event_hooks.c my_mlx_functions.c manipulate_camera.c manipulate_object.c manipulate_light.c) \
	$(addprefix $(PARSE_DIR), parse_scene.c parse_utils.c parse_object.c parse_object_cap.c parse_light.c parse_types.c parse_error_check.c parse_scene_element.c parse_texture.c) \
	$(addprefix $(RENDER_DIR), compute_lighting.c intersect_ray_plane.c render_scene.c vector_operations1.c vector_operations2.c intersect_ray_cylinder.c intersect_ray_cone.c get_normal_vector.c closest_intersection.c intersect_ray_sphere.c compute_circle_intersection.c get_surface_color.c apply_bump_map.c convert_to_texture_space.c)

OBJ				=	$(SRC:.c=.o)

# -----------------------------------------------------------------------

all: $(NAME)

$(NAME): $(OBJ) $(MLX_LIB) $(LIBFT)
	@$(CC) $(OBJ) $(LIBFT_FLAGS) $(MLX_FLAGS) -o $(NAME)
	@echo "Linked into executable \033[0;32mminiRT\033[0m."

$(MLX_LIB):
	@make -C $(MLX_DIR)
ifeq ($(ARCH), x86_64)
	@cp $(MLX_DIR)$(MLX_LIB) .  # dylib 복사 (Apple Silicon에선 생략)
endif

$(LIBFT):
	@make -C $(LIBFT_DIR)

%.o: %.c $(INCLUDES) $(MLX_HEADER) $(LIBFT_HEADER)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I$(MLX_DIR) -I$(LIBFT_DIR) -Iincludes -c $< -o $@

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
ifeq ($(ARCH), x86_64)
	@$(RM) libmlx.dylib
	@echo "remove \033[0;31mlibmlx.dylib\033[0m."
endif
	@$(RM) $(NAME)
	@echo "remove \033[0;31mexecutable\033[0m."

re: fclean all

.PHONY: all clean fclean re
