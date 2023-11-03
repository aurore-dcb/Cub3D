NAME = cub3D

SRCS =	sources/main.c \
		sources/parsing.c \
		sources/check_config.c \
		sources/frees.c \
		sources/utils.c
OBJS = ${SRCS:sources/%.c=objects/%.o}
HEADER = headers/

CC = cc
CFLAGS = -Lminilibx-linux -g3#-Wall -Wextra -Werror 
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
			${CC} -I $(HEADER) -I libft/ ${CFLAGS} -o ${NAME} ${OBJS} ${LIBFT_LIB} ${MLX_LIB} ${MLX_FLAGS}

objects/%.o: sources/%.c
			mkdir -p $(dir $@)
			${CC} -I $(HEADER) -I libft/ ${CFLAGS} -c -o $@ $^

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
