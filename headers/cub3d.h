#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include "libft.h"
# include <math.h>
# include <stdio.h>
# include <unistd.h>

typedef struct s_map
{
	char	**map;
	int		nb_player;
	int		first_row;
	int		nb_col;
	int		nb_line;
}			t_map;

// parsing
// int	ft_parsing(int argc, char **argv, char **env);
int			read_file(t_map *data, char *file);
int			get_map(t_map *data, char *file);

// free
void		free_char(char **tableau);
void		free_char_spe(char **tableau, int len);

// parsing_utils
int			is_spaces(char c);
int			is_digit_map(char c);
int			is_carac_map(char c);
int			test_valid_carac(char c);

#endif