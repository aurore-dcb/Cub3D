#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include "libft.h"
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"

typedef struct s_map
{
	char	**map;
	int		nb_player;
	int		first_row;
	int		nb_col;
	int		nb_line;
}				t_map;

// parsing
// int	ft_parsing(int argc, char **argv, char **env);
int	read_file(t_map *data, char *file);

#endif