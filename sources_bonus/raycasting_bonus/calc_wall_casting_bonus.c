/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_wall_casting_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 13:22:33 by aducobu           #+#    #+#             */
/*   Updated: 2023/11/21 13:57:02 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_side(t_map *data)
{
	data->ray.hit = 0;
	if (data->ray.raydirx < 0)
	{
		data->ray.step_x = -1;
		data->ray.side_dist_x = (data->posx - data->ray.map_x)
			* data->ray.delta_dist_x;
	}
	else
	{
		data->ray.step_x = 1;
		data->ray.side_dist_x = (data->ray.map_x + 1.0 - data->posx)
			* data->ray.delta_dist_x;
	}
	if (data->ray.raydiry < 0)
	{
		data->ray.step_y = 1;
		data->ray.side_dist_y = (data->ray.map_y + 1.0 - data->posy)
			* data->ray.delta_dist_y;
	}
	else
	{
		data->ray.step_y = -1;
		data->ray.side_dist_y = (data->posy - data->ray.map_y)
			* data->ray.delta_dist_y;
	}
}

void	dda_algo(t_map *data)
{
	while (data->ray.hit == 0)
	{
		if (data->ray.side_dist_x < data->ray.side_dist_y)
		{
			data->ray.side_dist_x += data->ray.delta_dist_x;
			data->ray.map_x += data->ray.step_x;
			data->ray.side = 0;
		}
		else
		{
			data->ray.side_dist_y += data->ray.delta_dist_y;
			data->ray.map_y += data->ray.step_y;
			data->ray.side = 1;
		}
		if (data->map[data->ray.map_y][data->ray.map_x] == '1'
			|| (data->doors == 1
				&& data->map[data->ray.map_y][data->ray.map_x] == 'D'))
			data->ray.hit = 1;
	}
}

void	wall_size(t_map *data)
{
	if (data->ray.side == 0)
		data->ray.perp_wall_dist = data->ray.side_dist_x
			- data->ray.delta_dist_x;
	else
		data->ray.perp_wall_dist = data->ray.side_dist_y
			- data->ray.delta_dist_y;
	data->ray.line_height = (int)(data->height / data->ray.perp_wall_dist);
	data->ray.pitch = 100;
	data->ray.draw_start = -data->ray.line_height / 2 + data->height / 2
		+ data->ray.pitch;
	if (data->ray.draw_start < 0)
		data->ray.draw_start = 0;
	data->ray.draw_end = data->ray.line_height / 2 + data->height / 2
		+ data->ray.pitch;
	if (data->ray.draw_end >= data->height)
		data->ray.draw_end = data->height - 1;
}
