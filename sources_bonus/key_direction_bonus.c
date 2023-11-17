#include "cub3d_bonus.h"

void	left_key(t_map *data)
{
	double	rad;
	double	dx;
	double	px;

	dx = data->dirX;
	px = data->planeX;
	rad = (ALPHA * PI) / 180;
	data->dirX = data->dirX * cos(rad) - data->dirY * sin(rad);
	data->dirY = dx * sin(rad) + data->dirY * cos(rad);
	data->planeX = data->planeX * cos(rad) - data->planeY * sin(rad);
	data->planeY = px * sin(rad) + data->planeY * cos(rad);
}

void	right_key(t_map *data)
{
	double	rad;
	double	dx;
	double	px;

	dx = data->dirX;
	px = data->planeX;
	rad = (-ALPHA * PI) / 180;
	data->dirX = data->dirX * cos(rad) - data->dirY * sin(rad);
	data->dirY = dx * sin(rad) + data->dirY * cos(rad);
	data->planeX = data->planeX * cos(rad) - data->planeY * sin(rad);
	data->planeY = px * sin(rad) + data->planeY * cos(rad);
}
