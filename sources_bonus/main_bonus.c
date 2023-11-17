#include "cub3d_bonus.h"

void	init_map(t_map *data)
{
	ft_memset(data, 0, sizeof(t_map));
	data->x_player = -1;
	data->y_player = -1;
	data->width = 800;
	data->height = 600;
	data->tex_height = 64;
	data->tex_width = 64;
	data->w = 0;
	data->a = 0;
	data->s = 0;
	data->d = 0;
	data->right = 0;
	data->left = 0;
	data->shift = 0;
	data->doors = 1;
	data->dis_map = -1;
	data->b_left = -1;
	data->nb_sprites = 0;
	data->nb_doors = 0;
	ft_memset(&data->ray, 0, sizeof(t_ray));
	ft_memset(&data->sprite, 0, sizeof(t_coll));
}

int	loop(t_map *d)
{
	d->mlx_ptr = mlx_init();
	if (!d->mlx_ptr)
		return (printf("Error\nCannot init window\n"), 0);
	d->win_ptr = mlx_new_window(d->mlx_ptr, d->width, d->height, "Cub3D");
	if (!d->win_ptr)
		return (printf("Error\nCannot display window\n"), free(d->win_ptr), 0);
	if (!load_tex(d))
		return (0);
	d->main.img = mlx_new_image(d->mlx_ptr, d->width, d->height);
	if (!d->main.img)
		return (0);
	d->main.data = (int *)mlx_get_data_addr(d->main.img, &d->main.bpp,
			&d->main.size, &d->main.endian);
	if (!d->main.data)
		return (0);
	display(d);
	mlx_mouse_move(d->mlx_ptr, d->win_ptr, d->width / 2, d->height / 2);
	mlx_mouse_hook(d->win_ptr, mouse_click, d);
	mlx_hook(d->win_ptr, 6, 1L << 6, &mouse_move, d);
	mlx_hook(d->win_ptr, 2, 1L << 0, key_press, d);
	mlx_hook(d->win_ptr, 3, 1L << 1, key_release, d);
	mlx_hook(d->win_ptr, 17, 1L << 17, mlx_loop_end, d->mlx_ptr);
	mlx_loop_hook(d->mlx_ptr, key_hook, d);
	mlx_loop(d->mlx_ptr);
	return (1);
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
	direction_begin(&data);
	if (!loop(&data))
		return (free_all(&data), 1);
	free_all(&data);
	return (0);
}
