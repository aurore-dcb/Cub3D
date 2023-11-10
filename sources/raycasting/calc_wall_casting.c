#include "cub3d.h"

void	init_side(t_map *data)
{
	if (data->ray.rayDirX < 0)
	{
		data->ray.stepX = -1;
		data->ray.sideDistX = (data->posX - data->ray.mapX)
			* data->ray.deltaDistX;
	}
	else
	{
		data->ray.stepX = 1;
		data->ray.sideDistX = (data->ray.mapX + 1.0 - data->posX)
			* data->ray.deltaDistX;
	}
	if (data->ray.rayDirY < 0)
	{
		data->ray.stepY = 1;
		data->ray.sideDistY = (data->ray.mapY + 1.0 - data->posY)
			* data->ray.deltaDistY;
	}
	else
	{
		data->ray.stepY = -1;
		data->ray.sideDistY = (data->posY - data->ray.mapY)
			* data->ray.deltaDistY;
	}
}

void	dda_algo(t_map *data)
{
	while (data->ray.hit == 0)
	{
		if (data->ray.sideDistX < data->ray.sideDistY)
		{
			data->ray.sideDistX += data->ray.deltaDistX;
			data->ray.mapX += data->ray.stepX;
			data->ray.side = 0;
		}
		else
		{
			data->ray.sideDistY += data->ray.deltaDistY;
			data->ray.mapY += data->ray.stepY;
			data->ray.side = 1;
		}
		// on s'est deplacer jusqu'au prochain x ou y entier
		// donc verifier si c'est un mur
		if (data->map[data->ray.mapY][data->ray.mapX] == '1')
			data->ray.hit = 1;
	}
}

void	wall_size(t_map *data)
{
	//Caculer la distance entre le plan camera et le mur
	if (data->ray.side == 0)
		data->ray.perpWallDist = data->ray.sideDistX - data->ray.deltaDistX;
	else
		data->ray.perpWallDist = data->ray.sideDistY - data->ray.deltaDistY;
	data->ray.pitch = 100;
	//Calculer la taille du segment qu'il faut dessiner
	//cad la hauteur du mur en fonction de sa distance avec le plan camera
	data->ray.line_height = (int)(data->height / data->ray.perpWallDist);
	data->ray.drawStart = -(data->ray.line_height) / 2 + data->height / 2
		+ data->ray.pitch;
	if (data->ray.drawStart < 0)
		data->ray.drawStart = 0;
	data->ray.drawEnd = data->ray.line_height / 2 + data->height / 2
		+ data->ray.pitch;
	if (data->ray.drawEnd >= data->height)
		data->ray.drawEnd = data->height - 1;
}
