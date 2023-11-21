/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_casting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:01:09 by rmeriau           #+#    #+#             */
/*   Updated: 2023/11/21 12:17:37 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	wall_orientation(t_map *data)
{
	if (data->ray.side == 0)
	{
		if (data->ray.stepx == 1)
			data->ray.wall_orient = 3;
		else if (data->ray.stepx == -1)
			data->ray.wall_orient = 2;
	}
	else if (data->ray.side == 1)
	{
		if (data->ray.stepy == 1)
			data->ray.wall_orient = 1;
		else if (data->ray.stepy == -1)
			data->ray.wall_orient = 0;
	}
}

void	pixel_color(t_map *data, int tex_x, int tex_y, int x)
{
	int				y;
	unsigned int	color;

	y = data->ray.drawstart;
	while (y <= data->ray.drawend)
	{
		tex_y = (int)data->ray.texpos & (data->tex_height - 1);
		data->ray.texpos += data->ray.step;
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
		data->ray.wallx = data->posy - data->ray.perpwalldist
			* data->ray.raydiry;
	else
		data->ray.wallx = data->posx + data->ray.perpwalldist
			* data->ray.raydirx;
	data->ray.wallx -= floor(data->ray.wallx);
	tex_x = (int)(data->ray.wallx * (double)(data->tex_width));
	if (data->ray.side == 0 && data->ray.raydirx > 0)
		tex_x = data->tex_width - tex_x - 1;
	if (data->ray.side == 1 && data->ray.raydiry < 0)
		tex_x = data->tex_width - tex_x - 1;
	data->ray.step = 1.0 * data->tex_height / data->ray.line_height;
	data->ray.texpos = (data->ray.drawstart - data->ray.pitch - data->height / 2
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
		data->ray.camerax = 2 * x / (double)data->width - 1;
		data->ray.raydirx = data->dirx + data->planex * data->ray.camerax;
		data->ray.raydiry = data->diry + data->planey * data->ray.camerax;
		data->ray.mapx = (int)data->posx;
		data->ray.mapy = (int)data->posy;
		if (data->ray.raydirx == 0)
			data->ray.deltadistx = pow(10, 30);
		else
			data->ray.deltadistx = fabs(1 / data->ray.raydirx);
		if (data->ray.raydiry == 0)
			data->ray.deltadisty = pow(10, 30);
		else
			data->ray.deltadisty = fabs(1 / data->ray.raydiry);
		data->ray.hit = 0;
		init_side(data);
		dda_algo(data);
		wall_size(data);
		textures(data, x);
	}
}
