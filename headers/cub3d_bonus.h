#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include "libft.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define PI 3.14159265358979323846
# define ALPHA 0.8
# define ALPHA_MOUSE 3

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
	double			cameraX;
	double			rayDirX;
	double			rayDirY;
	int				mapX;
	int				mapY;
	double			sideDistX;
	double			sideDistY;
	double			deltaDistX;
	double			deltaDistY;
	int				stepX;
	int				stepY;
	int				hit;
	int				side;
	double			perpWallDist;
	int				line_height;
	int				pitch;
	int				drawStart;
	int				drawEnd;
	int				wall_orient;
	double			wallX;
	double			step;
	double			texPos;
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
	double			*Zbuffer;
	int				*sprite_order;
	double			*sprite_dist;

	double			spritex;
	double			spritey;
	double			invDet;
	double			transformx;
	double			transformy;
	int				sprite_screenx;

	int				spriteHeight;
	int				drawStartY;
	int				drawEndY;
	int				spriteWidth;
	int				drawStartX;
	int				drawEndX;

	int				texX;
	int				d;
	int				texY;
	unsigned int	color;
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
	double			posX;
	double			posY;
	double			dirX;
	double			dirY;
	double			planeX;
	double			planeY;
	t_image			img;
	t_image			main;
	t_coll			sprite;
	int				tex_width;
	int				tex_height;
	char			*path_N;
	char			*path_S;
	char			*path_E;
	char			*path_W;
	char			*path_D;
	char			*path_CO;
	char			*F_color;
	char			*C_color;
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
int					is_carac_minimap(char c);
int					is_carac_map(char c, t_map *data);
int					test_valid_carac(char c, t_map *data);
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

void				sprite_casting(t_map *data);
int					init_sprite(t_map *data);
void				take_coin(t_map *data);
int					nb_sprite(t_map *data);

// load
int					load_img(t_map *data, t_image *img, char *path, int i);
int					load_tex_part2(t_map *data);
int					load_tex(t_map *data);

#endif