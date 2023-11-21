/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_casting_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 13:22:58 by aducobu           #+#    #+#             */
/*   Updated: 2023/11/21 13:57:20 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	wall_orientation(t_map *data)
{
	if (data->map[data->ray.map_y][data->ray.map_x] == 'D')
		data->ray.wall_orient = 4;
	else if (data->ray.side == 0)
	{
		if (data->ray.step_x == 1)
			data->ray.wall_orient = 3;
		else if (data->ray.step_x == -1)
			data->ray.wall_orient = 2;
	}
	else if (data->ray.side == 1)
	{
		if (data->ray.step_y == 1)
			data->ray.wall_orient = 1;
		else if (data->ray.step_y == -1)
			data->ray.wall_orient = 0;
	}
}

void	pixel_color(t_map *data, int tex_x, int tex_y, int x)
{
	int				y;
	unsigned int	color;

	y = data->ray.draw_start;
	while (y <= data->ray.draw_end)
	{
		tex_y = (int)data->ray.tex_pos & (data->tex_height - 1);
		data->ray.tex_pos += data->ray.step;
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
		data->ray.wall_x = data->posy - data->ray.perp_wall_dist
			* data->ray.raydiry;
	else
		data->ray.wall_x = data->posx + data->ray.perp_wall_dist
			* data->ray.raydirx;
	data->ray.wall_x -= floor(data->ray.wall_x);
	tex_x = (int)(data->ray.wall_x * (double)(data->tex_width));
	if (data->ray.side == 0 && data->ray.raydirx > 0)
		tex_x = data->tex_width - tex_x - 1;
	if (data->ray.side == 1 && data->ray.raydiry < 0)
		tex_x = data->tex_width - tex_x - 1;
	data->ray.step = 1.0 * data->tex_height / data->ray.line_height;
	data->ray.tex_pos = (data->ray.draw_start - data->ray.pitch - data->height
			/ 2 + data->ray.line_height / 2) * data->ray.step;
	wall_orientation(data);
	pixel_color(data, tex_x, tex_y, x);
}

void	wall_casting(t_map *data)
{
	int	x;

	x = -1;
	while (++x < data->width)
	{
		data->ray.camera_x = 2 * x / (double)data->width - 1;
		data->ray.raydirx = data->dirx + data->planex * data->ray.camera_x;
		data->ray.raydiry = data->diry + data->planey * data->ray.camera_x;
		data->ray.map_x = (int)data->posx;
		data->ray.map_y = (int)data->posy;
		if (data->ray.raydirx == 0)
			data->ray.delta_dist_x = pow(10, 30);
		else
			data->ray.delta_dist_x = fabs(1 / data->ray.raydirx);
		if (data->ray.raydiry == 0)
			data->ray.delta_dist_y = pow(10, 30);
		else
			data->ray.delta_dist_y = fabs(1 / data->ray.raydiry);
		init_side(data);
		dda_algo(data);
		wall_size(data);
		textures(data, x);
		if (data->nb_sprites > 0)
			data->sprite.z_buffer[x] = data->ray.perp_wall_dist;
	}
}
