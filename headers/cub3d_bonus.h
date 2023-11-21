/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 13:27:55 by aducobu           #+#    #+#             */
/*   Updated: 2023/11/21 13:55:44 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include "libft.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <unistd.h>

# define PI 3.14159265358979323846
# define ALPHA 0.8
# define ALPHA_MOUSE 3
# define UDIV 2
# define VDIV 2
# define VMOVE 500

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
	double			camera_x;
	double			raydirx;
	double			raydiry;
	int				map_x;
	int				map_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	double			perp_wall_dist;
	int				line_height;
	int				pitch;
	int				draw_start;
	int				draw_end;
	int				wall_orient;
	double			wall_x;
	double			step;
	double			tex_pos;
}					t_ray;

typedef struct s_sprite
{
	double			x;
	double			y;
	int				texture;
}					t_sprite;

typedef struct s_pair
{
	double			first;
	int				second;
}					t_pair;

typedef struct s_coll
{
	t_sprite		*sprite;
	double			*z_buffer;
	int				*sprite_order;
	double			*sprite_dist;
	double			spritex;
	double			spritey;
	double			inv_det;
	double			transformx;
	double			transformy;
	int				sprite_screenx;
	int				sprite_height;
	int				draw_starty;
	int				draw_endy;
	int				sprite_width;
	int				draw_startx;
	int				draw_endx;
	int				tex_x;
	int				d;
	int				tex_y;
	unsigned int	color;
	clock_t			current_time;
	double			elapsed_time;
	int				stripe;
	int				vmove_screen;
}					t_coll;

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
	t_coll			sprite;
	int				tex_width;
	int				tex_height;
	char			*path_n;
	char			*path_s;
	char			*path_e;
	char			*path_w;
	char			*path_d;
	char			*path_co;
	char			*f_color;
	char			*c_color;
	int				**tex;
	int				len_tex;
	unsigned int	**buffer;
	int				dis_map;
	int				w;
	int				s;
	int				d;
	int				a;
	int				right;
	int				left;
	int				shift;
	double			speed;
	int				doors;
	int				mx;
	int				b_left;
	int				nb_sprites;
	int				nb_doors;
	clock_t			start_time;
}					t_map;

// main
void				init_map(t_map *data);
int					load_img(t_map *data, t_image *img, char *path, int i);
int					load_tex(t_map *data);
int					loop(t_map *data);
// frees_utils
void				free_tab(char **tab);
void				free_tab_int(int **buf, t_map *data, int n);
void				free_buffer(unsigned int **buf, t_map *data);
void				free_char_spe(char **tableau, int len);
// frees
void				free_all2(t_map *data);
void				free_all(t_map *data);
// handle_key
void				w_key(t_map *data);
void				s_key(t_map *data);
void				a_key(t_map *data);
void				d_key(t_map *data);
// key_press
int					key_hook(t_map *data);
int					key_press(int keycode, t_map *data);
int					key_release(int keycode, t_map *data);
void				left_key(t_map *data);
void				right_key(t_map *data);
// mouse_key
void				mouse_y(t_map *data);
void				mouse_x(t_map *data);
int					mouse_move(int x, int y, t_map *data);
int					mouse_click(int button, int x, int y, t_map *data);
// check_config_utils
int					color_format(char *tab);
int					check_color(t_map *data, char **tab);
int					check_texture_paths(t_map *data, char **tab);
int					if_check_texture(t_map *data, int i, char **tab);
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
int					test_rows(t_map *data);
int					test_player(t_map *data);
int					test_invalid_char(t_map *data);
int					do_end_parse_map(t_map *data, int i, int empty_line);
int					beg_parse_map(t_map *data);
// parsing_test
int					test_cols_beg(t_map *data);
int					do_test_cols_end(t_map *data, int i, int j);
int					test_cols_end(t_map *data);
int					do_test_empty(t_map *data, int i);
int					test_empty(t_map *data);
// parsing_utils
int					is_sp(char c);
int					is_digit_map(char c);
int					is_carac_minimap(char c);
int					is_carac_map(char c, t_map *data);
int					test_valid_carac(char c, t_map *data);
// parsing
int					begin_line(char *line);
int					read_file(t_map *data, char *line, int fd);
int					ft_extantion(char *map);
void				get_nb_line(t_map *data);
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
// minimap utils
void				draw_rectangle(t_map *data, t_2D square, int size,
						int color);
void				draw_circle(t_map *data, t_2D p, int rad, int color);
// minimap
void				end_draw_fixed(t_map *d, t_2D p, t_2D square,
						int pixel_size);
void				do_draw_fixed(t_map *d, t_2D start, t_2D end,
						int pixel_size);
void				draw_fixed_mini_map(t_map *data, t_2D view, int pixel_size);
int					mini_map(t_map *data);
// sprite utils
void				fill_sprite(t_map *data);
int					init_sprite(t_map *data);
int					nb_sprite(t_map *data);
void				sort_order(t_pair *orders, int nb);
void				sort_sprites(int *order, double *dist, int nb);
// sprite casting
void				take_coin(t_map *data);
void				change_bright(int color, int red_value, t_map *data, int y);
void				color_texture(t_map *data, t_coll *s);
void				texture_height(t_map *data, t_coll *s, int i);
void				sprite_casting(t_map *data);
// load
int					load_img(t_map *data, t_image *img, char *path, int i);
int					load_tex_part2(t_map *data);
int					load_tex(t_map *data);

#endif