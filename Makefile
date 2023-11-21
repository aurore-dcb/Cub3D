# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/21 13:28:04 by aducobu           #+#    #+#              #
#    Updated: 2023/11/21 14:03:49 by aducobu          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
NAME_BONUS = cub3D_bonus

SRCS =	${addprefix sources/, \
			${addprefix parsing/, \
					parsing.c \
					parsing_utils.c \
					parsing_test.c \
					parsing_player.c \
					check_config.c \
					check_config_utils.c \
					get_map.c \
					ft_split_char.c \
				} \
			${addprefix raycasting/, \
					display.c \
					display_utils.c \
					wall_casting.c \
					calc_wall_casting.c \
					floor_casting.c \
				} \
			main.c \
			frees.c \
			key_press.c \
			handle_key.c \
			}

SRCS_BONUS =	${addprefix sources_bonus/, \
			${addprefix parsing_bonus/, \
					parsing_bonus.c \
					parsing_utils_bonus.c \
					parsing_test_bonus.c \
					parsing_player_bonus.c \
					check_config_bonus.c \
					check_config_utils_bonus.c \
					get_map_bonus.c \
					ft_split_char_bonus.c \
				} \
			${addprefix raycasting_bonus/, \
					display_bonus.c \
					display_utils_bonus.c \
					wall_casting_bonus.c \
					calc_wall_casting_bonus.c \
					floor_casting_bonus.c \
					sprite_casting_bonus.c \
					sprite_utils_bonus.c \
				} \
			main_bonus.c \
			frees_bonus.c \
			frees_utils_bonus.c \
			key_press_bonus.c \
			handle_key_bonus.c \
			mouse_key_bonus.c \
			mini_map_bonus.c \
			mini_map_utils_bonus.c \
			load_bonus.c \
			key_direction_bonus.c \
			}

OBJS = ${SRCS:sources/%.c=objects/%.o}
OBJS_BONUS = ${SRCS_BONUS:sources_bonus/%.c=objects_bonus/%.o}
HEADER = -I headers/ -I libft/ -I mlx

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 
MLX_FLAGS = -Lminilibx-linux -lmlx -lXext -lX11
RM = rm -rf

LIBFT_DIR	= libft
LIBFT_LIB	= libft/libft.a
MLX_DIR		= minilibx-linux

all:		${NAME}

${NAME}:	${OBJS}
			make -C ${LIBFT_DIR}
			make -C ${MLX_DIR}
			${CC} ${CFLAGS} $(HEADER) -o ${NAME} ${OBJS} ${MLX_FLAGS} ${LIBFT_LIB} -lm

objects/%.o: sources/%.c
			mkdir -p $(dir $@)
			${CC} ${CFLAGS} $(HEADER) -c -o $@ $^

bonus: $(NAME_BONUS)

${NAME_BONUS}:	${OBJS_BONUS}
			make -C ${LIBFT_DIR}
			make -C ${MLX_DIR}
			${CC} ${CFLAGS} $(HEADER) -o ${NAME_BONUS} ${OBJS_BONUS} ${MLX_FLAGS} ${LIBFT_LIB} -lm

objects_bonus/%.o: sources_bonus/%.c
			mkdir -p $(dir $@)
			${CC} ${CFLAGS} $(HEADER) -c -o $@ $^

clean:
			${RM} objects
			${RM} objects_bonus
			make -C libft clean
			make -C minilibx-linux clean
			
fclean:		clean
			${RM} ${NAME}
			${RM} ${NAME}_bonus
			make -C libft fclean

norm:
			norminette sources
			norminette sources_bonus
			norminette libft
			norminette headers
			
re:			fclean all
