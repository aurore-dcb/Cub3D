#include "cub3d.h"

unsigned int	get_color(t_map *data)
{
	unsigned int	color;
	char			**comp;

	comp = ft_split_char(data->C_color, ',');
	color = ((unsigned int)ft_atoi(comp[0]) << 16 | (unsigned int)ft_atoi(comp[1]) << 8 | (unsigned int)ft_atoi(comp[2]));
	free_tab(comp);
    return (color);
}

void	floor_casting(t_map *data)
{
	int y;
	int x;
	unsigned int color_ceiling;
	// unsigned int color_floor;
    unsigned int color;
	t_floor floor;

	floor = data->floor;
	y = -1;
	while (++y < data->height)
	{
		floor.rayDirX0 = data->dirX - data->planeX;
		floor.rayDirY0 = data->dirY - data->planeY;
		floor.rayDirX1 = data->dirX + data->planeX;
		floor.rayDirY1 = data->dirY + data->planeY;
		floor.p = y - data->height / 2;
		floor.pos_z = 0.5 * data->height;
		floor.row_distance = floor.pos_z / floor.p;
		floor.floor_stepx = floor.row_distance * (floor.rayDirX1
				- floor.rayDirX0) / data->height;
		floor.floor_stepy = floor.row_distance * (floor.rayDirY1
				- floor.rayDirY0) / data->height;
		floor.floorx = data->posX + floor.row_distance * floor.rayDirX0;
		floor.floory = data->posY + floor.row_distance * floor.rayDirY0;
		x = -1;
		while (++x < data->width)
		{
			floor.cellx = (int)floor.floorx;
			floor.celly = (int)floor.floory;
			floor.floorx += floor.floor_stepx;
			floor.floory += floor.floor_stepy;
			// color = //fonction
            // color_ceiling = get_color(data);
			color_ceiling = 0;
            color = 200;
			data->buffer[y][x] = color_ceiling;
			data->buffer[data->height - y - 1][x] = color;
		}
	}
}