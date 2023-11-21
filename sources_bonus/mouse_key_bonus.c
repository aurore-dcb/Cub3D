/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_key_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 13:24:07 by aducobu           #+#    #+#             */
/*   Updated: 2023/11/21 13:52:28 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	mouse_y(t_map *data)
{
	double	old_dir_y;
	double	old_plane_y;
	double	rad;

	rad = (ALPHA_MOUSE * PI) / 180;
	old_dir_y = data->diry;
	data->diry = data->diry * cos(rad) - data->dirx * sin(rad);
	data->dirx = old_dir_y * sin(rad) + data->dirx * cos(rad);
	old_plane_y = data->planey;
	data->planey = data->planey * cos(rad) - data->planex * sin(rad);
	data->planex = old_plane_y * sin(rad) + data->planex * cos(rad);
}

void	mouse_x(t_map *data)
{
	double	rad;
	double	old_dir_x;
	double	old_plane_x;

	rad = (ALPHA_MOUSE * PI) / 180;
	old_dir_x = data->dirx;
	data->dirx = data->dirx * cos(rad) - data->diry * sin(rad);
	data->diry = old_dir_x * sin(rad) + data->diry * cos(rad);
	old_plane_x = data->planex;
	data->planex = data->planex * cos(rad) - data->planey * sin(rad);
	data->planey = old_plane_x * sin(rad) + data->planey * cos(rad);
}

int	mouse_move(int x, int y, t_map *data)
{
	if (data->b_left == 1)
	{
		mlx_mouse_move(data->mlx_ptr, data->win_ptr, data->width / 2,
			data->height / 2);
	}
	data->mx = x;
	(void)y;
	return (0);
}

int	mouse_click(int button, int x, int y, t_map *data)
{
	(void)x;
	(void)y;
	if (button == 1)
	{
		mlx_mouse_move(data->mlx_ptr, data->win_ptr, data->width / 2,
			data->height / 2);
		data->b_left *= -1;
	}
	return (0);
}
