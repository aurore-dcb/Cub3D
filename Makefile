NAME = cub3D

SRCS =	sources/main.c

OBJS = ${SRCS:sources/%.c=objects/%.o}

CC = cc
CFLAGS = -Lminilibx-linux #-Wall -Wextra -Werror 
MLX_FLAGS = -lmlx -lXext -lX11
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
			${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${LIBFT_LIB} ${MLX_LIB} ${MLX_FLAGS}

objects/%.o: sources/%.c
			mkdir -p $(dir $@)
			${CC} ${CFLAGS} -c -o $@ $^

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
