#include "cub3d.h"

void coor_direction_begin(t_map *data)
{
	printf("data->y_player = %d\n", data->y_player);
	printf("data->x_player = %d\n", data->x_player);
	if (data->map[data->x_player][data->y_player] == 'N')
	{
		data->dirY = 0;
		data->dirX = 1;
	}
	else if (data->map[data->x_player][data->y_player] == 'S')
	{
		data->dirY = 0;
		data->dirX = -1;
	}
	else if (data->map[data->x_player][data->y_player] == 'E')
	{
		data->dirY = 1;
		data->dirX = 0;
	}
	else if (data->map[data->x_player][data->y_player] == 'W')
	{
		data->dirY = -1;
		data->dirX = 0;
	}
	data->posX = (double)data->x_player + 0.5;
	data->posY = (double)data->y_player + 0.5;
}

//dessiner la colonne de pixels
void vertical_line(int x, int drawStart, int drawEnd, char *color, t_map *data)
{
	(void)color;
	while (drawStart <= drawEnd)
	{
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, drawStart, x, 0xFF0000);
		drawStart++;
	}
}