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
# define ALPHA 2

typedef struct s_2DPoint
{
    int x;
    int y;
}               t_2DPoint;

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
	double	cameraX;
	double	rayDirX; //coordonnees du vecteur rayon
	double	rayDirY;
	int		mapX; // coordonnees de la case dans laquelle on est (case de char **map)
	int		mapY;
	double	sideDistX; // longueur entre la position actuelle et le prochain mur en x ou en y
	double	sideDistY;
	double	deltaDistX; // longueur entre un mur en x et le prochain mur en x (pas la distance euclidienne)
	double	deltaDistY; // longueur entre un mur en y et le prochain mur en y
	int		stepX;        // direction dans laquelle se deplacer en x et en y (+1 ou -1) pour suivre le rayon
	int		stepY;
	int		hit;             // 1 si un mur a ete touche, 0 sinon
	int		side;            // est ce que c'est un mur N / S ou E / W qui a ete touche
	double	perpWallDist; // distance entre le plan camera et le mur
	int		line_height;     // hauteur du mur qu'on dessine
	int		pitch;
	int		drawStart;
	int		drawEnd;
	int		wall_orient;
	double	wallX;
	double	step;
	double	texPos;
}			t_ray;

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

	double			posX; // positions du player type double
	double			posY; // (et au milieu de la case au depart)
	double			dirX;
	double			dirY;
	double			planeX;
	double			planeY;

	t_image			img;
	int				tex_width;
	int				tex_height;
	char			*path_N;
	char			*path_S;
	char			*path_E;
	char			*path_W;
	char			*F_color;
	char			*C_color;
	int				**tex;
	unsigned int	**buffer;

	int				dis_map;
}					t_map;

int					mini_map(t_map *data);
// floor_casting
void				floor_casting(t_map *data);
void				floor_casting2(t_map *data);

// wall_casting
void				wall_orientation(t_map *data);
void				pixel_color(t_map *data, double texX, double texY, int x);
void				textures(t_map *data, int x);
void				wall_casting(t_map *data);
// calc_wall_catsing
void				init_side(t_map *data);
void				dda_algo(t_map *data);
void				wall_size(t_map *data);
// mini_map
int					load_tex(t_map *data);

// ft_split2
char				**ft_split_char(const char *str, char charset);
// parsing
int					read_file(t_map *data, char *line, int fd);
int					get_map(t_map *data, char *file);
int					begin_line(char *line);
// parsing_utils
int					is_sp(char c);
int					is_digit_map(char c);
int					is_carac_map(char c);
int					test_valid_carac(char c);
// parsing_test
int					test_rows(t_map *data);
int					test_cols_beg(t_map *data);
int					test_cols_end(t_map *data);
int					do_test_empty(t_map *data, int i);
int					test_empty(t_map *data);
// parsing_player
int					test_invalid_char(t_map *data);
int					test_player(t_map *data);
int					do_beg_parse_map(t_map *data, int i, int *empty_line);
int					do_end_parse_map(t_map *data, int i, int empty_line);
int					beg_parse_map(t_map *data);

int					ft_extantion(char *map);
int					ft_parsing(int argc, char **argv, char **env, t_map *data);
// check_config
char				*do_check_config(t_map *data, char *line, int fd);
int					check_config(char **argv, t_map *data);
int					check_map(t_map *data);
int					beg_parse_map(t_map *data);
// check_config_utils
int					color_format(char *tab);
int					check_color(t_map *data, char **tab);
int					check_texture_paths(t_map *data, char **tab);
int					check_texture(char *line, t_map *data);
// frees
void				free_char_spe(char **tableau, int len);
void				free_tab(char **tab);
void				free_buffer(unsigned int **buf);
void				free_data(t_map *data);
void				free_mlx(t_map *data);
// get_map
int					get_map_size(t_map *data, char *lign);
void				do_fill_map(t_map *data, char *lign, int i);
int					fill_map(t_map *data, char *lign, int fd);
int					get_map(t_map *data, char *file);
// key_press
int					key_hook(int keycode, t_map *data);
// display
int					init_buffer(t_map *data);
void				display(t_map *data);
// display_utils
void				coor_direction_begin(t_map *data);
void				draw(t_map *data);
//main
void				init_map(t_map *data);
void				display_map(char **map); // a supprimer a la fin
#endif