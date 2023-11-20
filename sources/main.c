/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmeriau <rmeriau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:01:26 by rmeriau           #+#    #+#             */
/*   Updated: 2023/11/20 11:29:21 by rmeriau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	ft_memset(&data->ray, 0, sizeof(t_ray));
}

int	load_img(t_map *data, t_image *img, char *path, int i)
{
	int	y;
	int	x;

	img->img = mlx_xpm_file_to_image(data->mlx_ptr, path, &data->tex_width,
			&data->tex_height);
	if (!img->img)
		return (printf("Error\nCannot load texture\n"), 0);
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->size,
			&img->endian);
	if (!img->data)
		return (printf("Error\nCannot load texture\n"), 0);
	data->tex[i] = malloc(sizeof(int) * (data->tex_height * data->tex_width));
	if (!data->tex[i])
		return (printf("Error\nMalloc textures\n"), 0);
	data->len_tex++;
	y = -1;
	while (++y < data->tex_height)
	{
		x = -1;
		while (++x < data->tex_width)
			data->tex[i][y * data->tex_width + x] = img->data[y
				* data->tex_width + x];
	}
	mlx_destroy_image(data->mlx_ptr, data->img.img);
	return (1);
}

int	load_tex(t_map *data)
{
	data->tex = malloc(sizeof(int *) * (data->nb_tex));
	if (!data->tex)
		return (printf("Error\nMalloc\n"), 0);
	if (!load_img(data, &data->img, data->path_n, 0))
		return (0);
	if (!load_img(data, &data->img, data->path_s, 1))
		return (0);
	if (!load_img(data, &data->img, data->path_w, 2))
		return (0);
	if (!load_img(data, &data->img, data->path_e, 3))
		return (0);
	return (1);
}

int	loop(t_map *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (printf("Error\nCannot init window\n"), 0);
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->width, data->height,
			"Cub3D");
	if (!data->win_ptr)
		return (printf("Error\nCannot display window\n"),
			free(data->win_ptr), 0);
	if (!load_tex(data))
		return (0);
	data->main.img = mlx_new_image(data->mlx_ptr, data->width, data->height);
	if (!data->main.img)
		return (0);
	data->main.data = (int *)mlx_get_data_addr(data->main.img, &data->main.bpp,
			&data->main.size, &data->main.endian);
	if (!data->main.data)
		return (0);
	display(data);
	mlx_hook(data->win_ptr, 2, 1L << 0, key_press, data);
	mlx_hook(data->win_ptr, 3, 1L << 1, key_release, data);
	mlx_hook(data->win_ptr, 17, 1L << 17, mlx_loop_end, data->mlx_ptr);
	mlx_loop_hook(data->mlx_ptr, key_hook, data);
	mlx_loop(data->mlx_ptr);
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
