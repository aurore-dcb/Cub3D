#include "cub3d.h"

void	display_map(char **map) // a supprimer a la fin
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			printf("%c", map[i][j]);
			j++;
		}
		i++;
		printf("\n");
	}
}

void	init_map(t_map *data)
{
	ft_memset(data, 0, sizeof(t_map));
	data->x_player = -1;
	data->y_player = -1;
	data->width = 800;
	data->height = 600;
	data->tex_height = 64;
	data->tex_width = 64;
	ft_memset(&data->ray, 0, sizeof(t_ray));
}

int load_img(t_map *data, t_image *img, char *path, int i)
{
	int	y;
	int	x;

	img->img = mlx_xpm_file_to_image(data->mlx_ptr, path, &data->tex_width, &data->tex_height);
	if (!img->img)
		return (printf("Error\nCannot load texture\n"), 0);
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->size, &img->endian);
	if (!img->data)
		return (printf("Error\nCannot load texture\n"), 0);
	data->tex[i] = malloc(sizeof(int) * (data->tex_height * data->tex_width));
	if (!data->tex[i])
		return (printf("Error\nMalloc textures\n"), 0);
	y = 0;
	while (y < data->tex_height)
	{
		x = 0;
		while (x < data->tex_width)
		{
			data->tex[i][y * data->tex_width + x] = img->data[y * data->tex_width + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(data->mlx_ptr, data->img.img);
	return (1);
}

int	load_tex(t_map *data)
{
	data->tex = malloc(sizeof(int *) * (data->nb_tex)); // pour 4 texture : remplacer par une variable nb_textures
	if (!data->tex)
		return (printf("Error\nMalloc\n"), 0);
	if (!load_img(data, &data->img, data->path_N, 0))
		return (0);
	if (!load_img(data, &data->img, data->path_S, 1))
		return (0);
	if (!load_img(data, &data->img, data->path_W, 2))
		return (0);
	if (!load_img(data, &data->img, data->path_E, 3))
		return (0);
	return (1);
}

void	loop(t_map *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
	{
		printf("Error\nCannot init window\n");
		return ;
	}
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->width, data->height,
			"Cub3D");
	if (!data->win_ptr)
		return (ft_printf("Error\nCannot display window\n"),
			free(data->win_ptr));
	if (!load_tex(data))
		return ;
	data->main.img = mlx_new_image(data->mlx_ptr, data->width, data->height);
	if (!data->main.img)
		return ;
	data->main.data = (int *)mlx_get_data_addr(data->main.img, &data->main.bpp, &data->main.size, &data->main.endian);
	if (!data->main.data)
		return ;
	display(data);
	mlx_hook(data->win_ptr, MotionNotify, PointerMotionMask, &mouse_move, data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, key_hook, data);
	mlx_hook(data->win_ptr, 17, 1L << 17, mlx_loop_end, data->mlx_ptr);
	mlx_loop(data->mlx_ptr);
}

int	main(int argc, char **argv, char **env)
{
	t_map	data;

	init_map(&data);
	if (!ft_parsing(argc, argv, env, &data))
		return (free_all(&data), 1);
	if (!get_map(&data, argv[1]))
		return (free_all(&data), 1);
	if (!check_map(&data))
		return (free_all(&data), 1);
	// display_map(data.map);
	coor_direction_begin(&data);
	loop(&data);
	free_all(&data);
	// free_mlx(&data);
	// free_data(&data);
	return (0);
}
