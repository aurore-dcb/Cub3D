#include "cub3d.h"

void coor_direction_begin(t_map *data)
{
	int player;
	player = data->x_player;
	data->x_player = data->y_player;
	data->y_player = player;

	if (data->map[data->y_player][data->x_player] == 'N')
	{
		data->dirY = 1;
		data->dirX = 0;
		data->planeX = 0.66;
		data->planeY = 0;
	}
	else if (data->map[data->y_player][data->x_player] == 'S')
	{
		data->dirY = -1;
		data->dirX = 0;
		data->planeX = -0.66;
		data->planeY = 0;
	}
	else if (data->map[data->y_player][data->x_player] == 'E')
	{
		data->dirY = 0;
		data->dirX = 1;
		data->planeX = 0;
		data->planeY = -0.66;
	}
	else if (data->map[data->y_player][data->x_player] == 'W')
	{
		data->dirY = 0;
		data->dirX = -1;
		data->planeX = 0;
		data->planeY = 0.66;
	}
	data->posX = (double)data->x_player + 0.5;
	data->posY = (double)data->y_player + 0.5;
}

void vertical_line(int x, int drawStart, int drawEnd, int color, t_map *data)
{
	while (drawStart <= drawEnd)
	{
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, drawStart, color);
		drawStart++;
	}
}

