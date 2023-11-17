#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include "libft.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define PI 3.14159265358979323846
# define ALPHA 0.8

typedef struct s_2D
{
	int				x;
	int				y;
}					t_2D;

typedef struct s_image
{
	void			*mlx_img;
	char			*addr;
	int				bpp;
	int				line_len;
	int				endian;
	void			*img;
	int				*data;
	int				size;
}					t_image;

typedef struct s_ray
{
	double			camerax;
	double			raydirx;
	double			raydiry;
	int				mapx;
	int				mapy;
	double			sidedistx;
	double			sidedisty;
	double			deltadistx;
	double			deltadisty;
	int				stepx;
	int				stepy;
	int				hit;
	int				side;
	double			perpwalldist;
	int				line_height;
	int				pitch;
	int				drawstart;
	int				drawend;
	int				wall_orient;
	double			wallx;
	double			step;
	double			texpos;
}					t_ray;

typedef struct s_map
{
	char			**map;
	void			*mlx_ptr;
	void			*win_ptr;
	int				width;
	int				height;
	int				nb_player;
	int				nb_col;
	int				nb_line;
	int				nb_tex;
	int				x_player;
	int				y_player;
	t_ray			ray;
	double			posx;
	double			posy;
	double			dirx;
	double			diry;
	double			planex;
	double			planey;
	t_image			img;
	t_image			main;
	int				tex_width;
	int				tex_height;
	char			*path_n;
	char			*path_s;
	char			*path_e;
	char			*path_w;
	char			*f_color;
	char			*c_color;
	int				**tex;
	int				len_tex;
	unsigned int	**buffer;
	int				w;
	int				s;
	int				d;
	int				a;
	int				right;
	int				left;
	double			speed;
}					t_map;

// main
void				init_map(t_map *data);
int					load_img(t_map *data, t_image *img, char *path, int i);
int					load_tex(t_map *data);
int					loop(t_map *data);
// frees
void				free_tab(char **tab);
void				free_tab_int(int **buf, t_map *data, int n);
void				free_buffer(unsigned int **buf, t_map *data);
void				free_char_spe(char **tableau, int len);
void				free_all(t_map *data);
// handle_key
void				w_key(t_map *data);
void				s_key(t_map *data);
void				a_key(t_map *data);
void				d_key(t_map *data);
// key_press
void				left_key(t_map *data);
void				right_key(t_map *data);
int					key_press(int keycode, t_map *data);
int					key_release(int keycode, t_map *data);
int					key_hook(t_map *data);
// check_config_utils
int					color_format(char *tab);
int					check_color(t_map *data, char **tab);
int					check_texture_paths(t_map *data, char **tab);
int					check_texture(char *line, t_map *data);
// check_config
char				*do_check_config(t_map *data, char *line, int fd);
int					check_config(char **argv, t_map *data);
int					check_map(t_map *data);
// ft_split_char
char				**ft_split_char(const char *str, char charset);
// get_map
int					get_map_size(t_map *data, char *lign);
void				do_fill_map(t_map *data, char *lign, int i);
int					fill_map(t_map *data, char *lign, int fd);
int					get_map(t_map *data, char *file);
// parsing_player
int					test_player(t_map *data);
int					test_invalid_char(t_map *data);
int					do_beg_parse_map(t_map *data, int i, int *empty_line);
int					do_end_parse_map(t_map *data, int i, int empty_line);
int					beg_parse_map(t_map *data);
// parsing_test
int					test_rows(t_map *data);
int					test_cols_beg(t_map *data);
int					test_cols_end(t_map *data);
int					do_test_empty(t_map *data, int i);
int					test_empty(t_map *data);
// parsing_utils
int					is_sp(char c);
int					is_digit_map(char c);
int					is_carac_map(char c);
int					test_valid_carac(char c);
// parsing
int					begin_line(char *line);
int					read_file(t_map *data, char *line, int fd);
int					ft_extantion(char *map);
int					ft_parsing(int argc, char **argv, char **env, t_map *data);
// display_utils
void				init_direction(t_map *data);
void				direction_begin(t_map *data);
// display
int					init_buffer(t_map *data);
void				display(t_map *data);
void				draw(t_map *data);
// floor_casting
unsigned int		get_color(char *s);
void				floor_casting(t_map *data);
// calc_wall_catsing
void				init_side(t_map *data);
void				dda_algo(t_map *data);
void				wall_size(t_map *data);
// wall_casting
void				wall_orientation(t_map *data);
void				pixel_color(t_map *data, int tex_x, int tex_y, int x);
void				textures(t_map *data, int x);
void				wall_casting(t_map *data);
#endif