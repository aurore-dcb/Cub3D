#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include "libft.h"
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_map
{
	char	**map;
	int		nb_player;
	int		first_row;
	int		nb_col;
	int		nb_line;
	char	*path_N;
	char	*path_S;
	char	*path_E;
	char	*path_W;
	char	*F_color;
	char	*C_color;
}			t_map;

// ft_split2
char	**ft_split_char(const char *str, char charset);
// parsing
// int	ft_parsing(int argc, char **argv, char **env);
int			read_file(t_map *data, char *file);
int			get_map(t_map *data, char *file);
// parsing_utils
int			is_spaces(char c);
int			is_digit_map(char c);
int			is_carac_map(char c);
int			test_valid_carac(char c);

int			ft_extantion(char *map);
int			ft_parsing(int argc, char **argv, char **env, t_map *data);
// check config
int			check_texture(char *line, t_map *data);
int			check_config(char **argv, t_map *data);
// frees
void		free_char_spe(char **tableau, int len);
void		free_tab(char **tab);
void		free_data(t_map *data);
#endif