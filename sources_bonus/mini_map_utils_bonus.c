#include "cub3d_bonus.h"

void	draw_rectangle(t_map *data, t_2D square, int size, int color)
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
			data->main.data[i * data->width + j] = color;
			j++;
		}
		i++;
	}
}

void	draw_circle(t_map *data, t_2D p, int rad, int color)
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
				data->main.data[i * data->width + j] = color;
			}
			j++;
		}
		i++;
	}
}
