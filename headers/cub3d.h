#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include "libft.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_map
{
	char	**map;
	char	*path_N;
	char	*path_S;
	char	*path_E;
	char	*path_W;
	char	*F_color;
	char	*C_color;
}			t_map;

// parsing
int			ft_extantion(char *map);
int			ft_parsing(int argc, char **argv, char **env, t_map *data);
// check config
int			check_texture(char *line, t_map *data);
int			check_config(char **argv, t_map *data);
// frees
void		free_tab(char **tab);
void		free_data(t_map *data);
#endif