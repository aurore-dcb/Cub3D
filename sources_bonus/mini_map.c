
#include "cub3d.h"

void	draw_rectangle(t_map *data, t_2DPoint square, int size, int color)
{
	int	i;
	int	j;

	i = square.y;
	j = 0;
	while (i < square.y + size)
	{
		j = square.x;
		while (j < square.x + size)
		{
			data->img.data[i * data->width + j] = color;
			j++;
		}
		i++;
	}
}

void	draw_circle(t_map *data, t_2DPoint p, int rad, int color)
{
	int	i;
	int	j;

	i = p.y - rad;
	j = 0;
	while (i <= p.y + rad)
	{
		j = p.x - rad;
		while (j <= p.x + rad)
		{
			if ((i - p.y) * (i - p.y) + (j - p.x) * (j - p.x) <= rad * rad)
			{
				data->img.data[i * data->width + j] = color;
			}
			j++;
		}
		i++;
	}
}

void	do_mini_map(t_map *data, int x, int y, int pixel_size)
{
	t_2DPoint	square;

	square.x = x * pixel_size;
	square.y = y * pixel_size;
	if (data->map[y][x] == '1')
	{
		draw_rectangle(data, square, pixel_size, 0x0000FF);
	}
	else
	{
		draw_rectangle(data, square, pixel_size, 0xFFFFFF);
	}
}

int	mini_map(t_map *data)
{
	t_2DPoint	p;
	int			pixel_size;
	int			x;
	int			y;

	pixel_size = 8;
	x = 0;
	y = 0;
	while (y < data->nb_line)
	{
		x = 0;
		while (x < data->nb_col - 1)
		{
			do_mini_map(data, x, y, pixel_size);
			x++;
		}
		y++;
	}
	p.x = data->posX * pixel_size;
	p.y = data->posY * pixel_size;
	draw_circle(data, p, pixel_size / 4, 0xFF0000);
	return (0);
}
