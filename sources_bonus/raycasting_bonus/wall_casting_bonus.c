#include "cub3d_bonus.h"

void	wall_orientation(t_map *data)
{
	if (data->map[data->ray.mapY][data->ray.mapX] == 'D')
		data->ray.wall_orient = 4;
	else if (data->ray.side == 0)
	{
		if (data->ray.stepX == 1)
			data->ray.wall_orient = 3;
		else if (data->ray.stepX == -1)
			data->ray.wall_orient = 2;
	}
	else if (data->ray.side == 1)
	{
		if (data->ray.stepY == 1)
			data->ray.wall_orient = 1;
		else if (data->ray.stepY == -1)
			data->ray.wall_orient = 0;
	}
}

void	pixel_color(t_map *data, int tex_x, int tex_y, int x)
{
	int				y;
	unsigned int	color;

	y = data->ray.drawStart;
	while (y < data->ray.drawEnd)
	{
		tex_y = (int)data->ray.texPos & (data->tex_height - 1);
		data->ray.texPos += data->ray.step;
		color = data->tex[data->ray.wall_orient][data->tex_height * tex_y
			+ tex_x];
		data->buffer[y][x] = color;
		y++;
	}
}

void	textures(t_map *data, int x)
{
	int	tex_x;
	int	tex_y;

	tex_x = 0;
	tex_y = 0;
	if (data->ray.side == 0)
		data->ray.wallX = data->posY - data->ray.perpWallDist
			* data->ray.rayDirY;
	else
		data->ray.wallX = data->posX + data->ray.perpWallDist
			* data->ray.rayDirX;
	data->ray.wallX -= floor(data->ray.wallX);
	tex_x = (int)(data->ray.wallX * (double)(data->tex_width));
	if (data->ray.side == 0 && data->ray.rayDirX > 0)
		tex_x = data->tex_width - tex_x - 1;
	if (data->ray.side == 1 && data->ray.rayDirY < 0)
		tex_x = data->tex_width - tex_x - 1;
	data->ray.step = 1.0 * data->tex_height / data->ray.line_height;
	data->ray.texPos = (data->ray.drawStart - data->ray.pitch - data->height / 2
			+ data->ray.line_height / 2) * data->ray.step;
	wall_orientation(data);
	pixel_color(data, tex_x, tex_y, x);
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
		if (nb_sprite(data) > 0)
            data->sprite.Zbuffer[x] = data->ray.perpWallDist;
	}
}
