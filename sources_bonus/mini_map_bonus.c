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

void	do_draw_fixed(t_map *d, t_2D start, t_2D end, int pixel_size)
{
	t_2D	square;
	t_2D	p;

	p.y = start.y;
	p.x = start.x;
	while (p.y <= end.y)
	{
		p.x = start.x;
		while (p.x <= end.x)
		{
			square.x = (p.x - start.x) * pixel_size;
			square.y = (p.y - start.y) * pixel_size;
			if (p.y < 0 || p.y >= d->nb_line || p.x < 0 || p.x >= d->nb_col)
			{
				p.x++;
				continue ;
			}
			else if (d->map[p.y][p.x] == '0' || is_carac_map(d->map[p.y][p.x]))
				draw_rectangle(d, square, pixel_size, 0xFFFFFF);
			else
				draw_rectangle(d, square, pixel_size, 0x0000FF);
			p.x++;
		}
		p.y++;
	}
}

void	draw_fixed_mini_map(t_map *data, t_2D view, int pixel_size)
{
	t_2D	start;
	t_2D	end;

	start.x = (int)data->posX - view.x;
	start.y = (int)data->posY - view.y;
	end.x = data->posX + view.x;
	end.y = data->posY + view.y;
	do_draw_fixed(data, start, end, pixel_size);
}

int	mini_map(t_map *data)
{
	t_2D	minimap_center;
	t_2D	view;
	int		pixel_size;

	pixel_size = 8;
	view.x = 5;
	view.y = 3;
	minimap_center.x = (view.x * 2 * pixel_size + 8) / 2;
	minimap_center.y = ((view.y + 1) * 2 * pixel_size - 8) / 2;
	draw_fixed_mini_map(data, view, pixel_size);
	draw_circle(data, minimap_center, pixel_size / 4, 0xFF0000);
	return (0);
}
