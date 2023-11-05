#include "cub3d.h"

void coor_direction_begin(t_map *data)
{
	printf("data->y_player = %d\n", data->y_player);
	printf("data->x_player = %d\n", data->x_player);
	if (data->map[data->y_player][data->x_player] == 'N')
	{
		data->dirX = 0;
		data->dirY = 1;
	}
	else if (data->map[data->y_player][data->x_player] == 'S')
	{
		data->dirX = 0;
		data->dirY = -1;
	}
	else if (data->map[data->y_player][data->x_player] == 'E')
	{
		data->dirX = 1;
		data->dirY = 0;
	}
	else if (data->map[data->y_player][data->x_player] == 'W')
	{
		data->dirX = -1;
		data->dirY = 0;
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