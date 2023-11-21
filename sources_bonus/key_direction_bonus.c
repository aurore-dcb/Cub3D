/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_direction_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 13:23:21 by aducobu           #+#    #+#             */
/*   Updated: 2023/11/21 13:52:28 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	left_key(t_map *data)
{
	double	rad;
	double	dx;
	double	px;

	dx = data->dirx;
	px = data->planex;
	rad = (ALPHA * PI) / 180;
	data->dirx = data->dirx * cos(rad) - data->diry * sin(rad);
	data->diry = dx * sin(rad) + data->diry * cos(rad);
	data->planex = data->planex * cos(rad) - data->planey * sin(rad);
	data->planey = px * sin(rad) + data->planey * cos(rad);
}

void	right_key(t_map *data)
{
	double	rad;
	double	dx;
	double	px;

	dx = data->dirx;
	px = data->planex;
	rad = (-ALPHA * PI) / 180;
	data->dirx = data->dirx * cos(rad) - data->diry * sin(rad);
	data->diry = dx * sin(rad) + data->diry * cos(rad);
	data->planex = data->planex * cos(rad) - data->planey * sin(rad);
	data->planey = px * sin(rad) + data->planey * cos(rad);
}
