#include "cub3d.h"

void	display(t_map *data)
{
	int	y;
	int	x;

	// FLOOR CASTING
	floor_casting(data);
	// WALL CASTING
	wall_casting(data);
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
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
	mini_map(data);
}
