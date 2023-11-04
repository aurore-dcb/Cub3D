#include "cub3d.h"

void coor_direction_begin(t_map *data)
{
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
