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
			data->main.data[i * data->width + j] = color;
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
				data->main.data[i * data->width + j] = color;
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
	if (data->map[y][x] == '0' || is_carac_map(data->map[y][x]))
	{
		draw_rectangle(data, square, pixel_size, 0xFFFFFF);
	}
	else
	{
		draw_rectangle(data, square, pixel_size, 0x0000FF);
	}
}

void draw_fixed_mini_map(t_map *data, int view_radius, int pixel_size)
{
    int startX = data->posX - view_radius;
    int startY = data->posY - view_radius;

    startX = (startX < 0) ? 0 : startX;
    startY = (startY < 0) ? 0 : startY;

    int endX = data->posX + view_radius;
    int endY = data->posY + view_radius;

    endX = (endX >= data->nb_col) ? data->nb_col - 1 : endX;
    endY = (endY >= data->nb_line) ? data->nb_line - 1 : endY;

    for (int y = startY; y <= endY; y++)
    {
        for (int x = startX; x <= endX; x++)
        {
            t_2DPoint square;
            square.x = (x - startX) * pixel_size;
            square.y = (y - startY) * pixel_size;

            if (data->map[y][x] == '0' || is_carac_map(data->map[y][x]))
            {
                draw_rectangle(data, square, pixel_size, 0xFFFFFF);
            }
            else
            {
                draw_rectangle(data, square, pixel_size, 0x0000FF);
            }
        }
    }
}

int mini_map(t_map *data)
{
    int pixel_size = 8;
    int view_radius = 5;  // Rayon de la vue autour du joueur

    draw_fixed_mini_map(data, view_radius, pixel_size);
    // Coordonnées du centre de la minimap
    t_2DPoint minimapCenter;
    minimapCenter.x = (view_radius * 2 * pixel_size + 8) / 2;
    minimapCenter.y = (view_radius * 2 * pixel_size - 8) / 2;

    // Coordonnées du cercle rouge au centre de la minimap
    t_2DPoint circleCenter;
    circleCenter.x = 30;
    circleCenter.y = 30;

    // Dessiner le cercle rouge au centre de la minimap
    draw_circle(data, minimapCenter, pixel_size / 4, 0xFF0000);


    return 0;
}
