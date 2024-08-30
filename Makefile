NAME			=	minirt
HEADER			=	minirt.h

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror

SRC				=	minirt.c
OBJ				=	$(patsubst %.c, %.o, $(SRC))

MLX				=	libmlx.dylib
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
LIBFT_OBJ		=	$(patsubst %.c, %.o, $(LIBFT_SRC))
LIBFT_HEADER	=	$(addprefix $(LIBFT_DIR), libft.h get_next_line.h)
LIBFT_FLAGS		=	-Llibft -lft

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	@$(CC) $(OBJ) $(LIBFT_FLAGS) $(MLX_FLAGS) -o $(NAME)
	@echo "\033[0;33mminirt\033[0m compiled."

$(MLX): $(MLX_DIR)$(MLX)
	@cp $(MLX_DIR)$(MLX) .

$(MLX_DIR)$(MLX):
	@make -C $(MLX_DIR)

$(LIBFT): $(LIBFT_SRC) $(LIBFT_HEADER)
	@make -C $(LIBFT_DIR)

%.o: %.c $(HEADER) $(MLX_HEADER) $(LIBFT_HEADER)
	@$(CC) $(CFLAGS) -Imlx -Ilibft -c $< -o $@

clean:
	@rm -f $(OBJ)
	@make -C $(LIBFT_DIR) fclean
	@make -C $(MLX_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@rm -f $(MLX)

re: fclean all

.PHONY: all clean fclean re
