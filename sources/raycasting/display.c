#include "cub3d.h"

void init_buffer(t_map *data)
{
	int x;
	int y;

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

void	display(t_map *data)
{
	int	y;
	int	x;

	// initialiser toutes les cases du buffer a 0
	init_buffer(data);
	// WALL CASTING
	wall_casting(data);
	// FLOOR CASTING
	floor_casting(data);
	draw(data);
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
			data->img.data[y * data->width + x] = data->buffer[y][x];
			x++;
		}
		y++;
	}
	mini_map(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
}
