#include "cub3d.h"

// void	init_side(t_map *data)
// {
// 	if (data->ray.rayDirX < 0)
// 	{
// 		data->ray.stepX = -1;
// 		data->ray.sideDistX = (data->posX - data->ray.mapX)
// 			* data->ray.deltaDistX;
// 	}
// 	else
// 	{
// 		data->ray.stepX = 1;
// 		data->ray.sideDistX = (data->ray.mapX + 1.0 - data->posX)
// 			* data->ray.deltaDistX;
// 	}
// 	if (data->ray.rayDirY < 0)
// 	{
// 		data->ray.stepY = 1;
// 		data->ray.sideDistY = (data->ray.mapY + 1.0 - data->posY)
// 			* data->ray.deltaDistY;
// 	}
// 	else
// 	{
// 		data->ray.stepY = -1;
// 		data->ray.sideDistY = (data->posY - data->ray.mapY)
// 			* data->ray.deltaDistY;
// 	}
// }

// void	dda_algo(t_map *data)
// {
// 	while (data->ray.hit == 0)
// 	{
// 		if (data->ray.sideDistX < data->ray.sideDistY)
// 		{
// 			data->ray.sideDistX += data->ray.deltaDistX;
// 			data->ray.mapX += data->ray.stepX;
// 			data->ray.side = 0;
// 		}
// 		else
// 		{
// 			data->ray.sideDistY += data->ray.deltaDistY;
// 			data->ray.mapY += data->ray.stepY;
// 			data->ray.side = 1;
// 		}
// 		// on s'est deplacer jusqu'au prochain x ou y entier
// 		// donc verifier si c'est un mur
// 		if (data->map[data->ray.mapY][data->ray.mapX] == '1')
// 			data->ray.hit = 1;
// 	}
// }

// void	wall_size(t_map *data)
// {
// 	//Caculer la distance entre le plan camera et le mur
// 	if (data->ray.side == 0)
// 		data->ray.perpWallDist = data->ray.sideDistX - data->ray.deltaDistX;
// 	else
// 		data->ray.perpWallDist = data->ray.sideDistY - data->ray.deltaDistY;
// 	data->ray.pitch = 100;
// 	//Calculer la taille du segment qu'il faut dessiner
// 	//cad la hauteur du mur en fonction de sa distance avec le plan camera
// 	data->ray.line_height = (int)(data->height / data->ray.perpWallDist);
// 	data->ray.drawStart = -(data->ray.line_height) / 2 + data->height / 2
// 		+ data->ray.pitch;
// 	if (data->ray.drawStart < 0)
// 		data->ray.drawStart = 0;
// 	data->ray.drawEnd = data->ray.line_height / 2 + data->height / 2
// 		+ data->ray.pitch;
// 	if (data->ray.drawEnd >= data->height)
// 		data->ray.drawEnd = data->height - 1;
// }

void	wall_orientation(t_map *data)
{
	data->ray.wall_orient = 0;
	if (data->ray.side == 0)
	{
		if (data->ray.stepX == 1) // est
			data->ray.wall_orient = 3;
		else if (data->ray.stepX == -1) //ouest
			data->ray.wall_orient = 2;
	}
	else if (data->ray.side == 1)
	{
		if (data->ray.stepY == 1) //sud
			data->ray.wall_orient = 1;
		else if (data->ray.stepY == -1) //nord
			data->ray.wall_orient = 0;
	}
}

void	pixel_color(t_map *data, double texX, double texY, int x)
{
	int	y;

	unsigned int color;
	y = data->ray.drawStart;
	while (y < data->ray.drawEnd)
	{
		color = 0;
		texY = (int)data->ray.texPos & (data->tex_height - 1);
		data->ray.texPos += data->ray.step;
		color = what_color(data, texX, texY, data->ray.wall_orient);
		if (data->ray.side == 1)
			color = (color >> 1) & 8355711;
		data->buffer[y][x] = color;
		y++;
	}
}

void	textures(t_map *data, int x)
{
	int		texX;
	int		texY;

	texX = 0;
	texY = 0;
	if (data->ray.side == 0)
		data->ray.wallX = data->posY + data->ray.perpWallDist * data->ray.rayDirY;
	else
		data->ray.wallX = data->posX + data->ray.perpWallDist * data->ray.rayDirX;
	data->ray.wallX -= floor(data->ray.wallX);
	texX = (int)(data->ray.wallX * (double)(data->tex_width));
	if (data->ray.side == 0 && data->ray.rayDirX > 0)
		texX = data->tex_width - texX - 1;
	if (data->ray.side == 1 && data->ray.rayDirY < 0)
		texX = data->tex_width - texX - 1;
	data->ray.step = 1.0 * data->tex_height / data->ray.line_height;
	data->ray.texPos = (data->ray.drawStart - data->ray.pitch - data->height / 2
			+ data->ray.line_height / 2) * data->ray.step;
	wall_orientation(data);
	pixel_color(data, texX, texY, x);
}

void	wall_casting(t_map *data)
{
	int	x;

	x = -1;
	while (++x < data->width)
	{
		data->ray.cameraX = 2 * x / (double)data->width - 1;
		data->ray.rayDirX = data->dirX + data->planeX * data->ray.cameraX;
		data->ray.rayDirY = data->dirY + data->planeY * data->ray.cameraX;
		data->ray.mapX = (int)data->posX;
		data->ray.mapY = (int)data->posY;
		if (data->ray.rayDirX == 0)
			data->ray.deltaDistX = pow(10, 30);
		else
			data->ray.deltaDistX = fabs(1 / data->ray.rayDirX);
		if (data->ray.rayDirY == 0)
			data->ray.deltaDistY = pow(10, 30);
		else
			data->ray.deltaDistY = fabs(1 / data->ray.rayDirY);
		data->ray.hit = 0;
		init_side(data);
		dda_algo(data);
		wall_size(data);
		textures(data, x);
	}
}
