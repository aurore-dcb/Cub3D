NAME = cub3D

SRCS =	sources/main.c \
		sources/parsing.c \
		sources/parsing_utils.c \
		sources/parsing_test.c \
		sources/parsing_player.c \
		sources/check_config.c \
		sources/check_config_utils.c \
		sources/get_map.c \
		sources/frees.c \
		sources/utils.c
OBJS = ${SRCS:sources/%.c=objects/%.o}
HEADER = -I headers/ -I libft/ -I mlx

CC = cc
CFLAGS = -Wall -Wextra -Werror  #-g3#-Wall -Wextra -Werror 
MLX_FLAGS = -Lminilibx-linux -lmlx -lXext -lX11
RM = rm -rf

LIBFT_DIR	= libft
LIBFT_LIB	= libft/libft.a
MLX_DIR		= minilibx-linux
MLX_LIB		= minilibx-linux/libmlx_Linux.a

all:		libft ${NAME}

libft/libft.a:
			make -C libft

minilibx-linux/libmlx_Linux.a:
			make -C minilibx-linux

${NAME}:	${OBJS} libft/libft.a minilibx-linux/libmlx_Linux.a
			${CC} ${CFLAGS} $(HEADER) -o ${NAME} ${OBJS} ${MLX_FLAGS} ${LIBFT_LIB} -lm

objects/%.o: sources/%.c
			mkdir -p $(dir $@)
			${CC} ${CFLAGS} $(HEADER) -c -o $@ $^

clean:
			${RM} objects
			make -C libft clean
			make -C minilibx-linux clean
			
fclean:		clean
			${RM} ${NAME}
			make -C libft fclean

norm:
			norminette sources
			norminette libft
			norminette headers
			
re:			fclean all
