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
	void	*mlx_ptr;
	void	*win_ptr;
	int		width;
	int		height;
	int		nb_player;
	int		nb_col;
	int		nb_line;
	int		x_player;
	int		y_player;
	char	*path_N;
	char	*path_S;
	char	*path_E;
	char	*path_W;
	char	*F_color;
	char	*C_color;
}			t_map;

// ft_split2
char		**ft_split_char(const char *str, char charset);
// parsing
int			read_file(t_map *data, char *line, int fd);
int			get_map(t_map *data, char *file);
int			begin_line(char *line);
// parsing_utils
int			is_sp(char c);
int			is_digit_map(char c);
int			is_carac_map(char c);
int			test_valid_carac(char c);
// parsing_test
int			test_rows(t_map *data);
int			test_cols_beg(t_map *data);
int			test_cols_end(t_map *data);
int			do_test_empty(t_map *data, int i);
int			test_empty(t_map *data);
// parsing_player
int			test_invalid_char(t_map *data);
int			test_player(t_map *data);
int			do_beg_parse_map(t_map *data, int i, int *empty_line);
int			do_end_parse_map(t_map *data, int i, int empty_line);
int			beg_parse_map(t_map *data);

int			ft_extantion(char *map);
int			ft_parsing(int argc, char **argv, char **env, t_map *data);
// check_config
char		*do_check_config(t_map *data, char *line, int fd);
int			check_config(char **argv, t_map *data);
int			check_map(t_map *data);
int			beg_parse_map(t_map *data);
// check_config_utils
int			color_format(char *tab);
int			check_color(t_map *data, char **tab);
int			check_texture_paths(t_map *data, char **tab);
int			check_texture(char *line, t_map *data);
// frees
void		free_char_spe(char **tableau, int len);
void		free_tab(char **tab);
void		free_data(t_map *data);
void		free_mlx(t_map *data);

// get_map
int			get_map_size(t_map *data, char *lign);
void		do_fill_map(t_map *data, char *lign, int i);
int			fill_map(t_map *data, char *lign, int fd);
int			get_map(t_map *data, char *file);

#endif