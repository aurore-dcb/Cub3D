#include "cub3d.h"

int init_buffer(t_map *data)
{
	int x;
	int y;

	y = 0;
	data->buffer = malloc(sizeof(unsigned int*) * (data->height));
	if (!data->buffer)
		return (0);
	while (y < data->height)
	{
		x = 0;
		data->buffer[y] = malloc(sizeof(unsigned int) * (data->width));
		if (!data->buffer[x])
			return (free_buffer(data->buffer), 0);
		while (x < data->width)
		{
			data->buffer[y][x] = 0;
			x++;
		}
		y++;
	}
	return (1);
}

void	display(t_map *data)
{
	int	y;
	int	x;

	// initialiser toutes les cases du buffer a 0
	if (!init_buffer(data))
	{
		printf("Error\nMalloc");
		return ;
	}
	// WALL CASTING
	wall_casting(data);
	// FLOOR CASTING
	floor_casting(data);
	draw(data);
	// Nettoyer le buffer
	// free_buffer(data->buffer);
	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			data->buffer[y][x] = 0;
			x++;
		}
		y++;
	}
}

void	draw(t_map *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			data->main.data[y * data->width + x] = data->buffer[y][x];
			x++;
		}
		y++;
	}
	if (data->dis_map == 0)
		mini_map(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->main.img, 0, 0);
}
