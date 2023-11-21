/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 13:22:43 by aducobu           #+#    #+#             */
/*   Updated: 2023/11/21 13:52:28 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_direction(t_map *data)
{
	if (data->map[data->y_player][data->x_player] == 'E')
	{
		data->diry = 0;
		data->dirx = 1;
		data->planex = 0;
		data->planey = -0.66;
	}
	else if (data->map[data->y_player][data->x_player] == 'W')
	{
		data->diry = 0;
		data->dirx = -1;
		data->planex = 0;
		data->planey = 0.66;
	}
	data->posx = (double)data->x_player + 0.5;
	data->posy = (double)data->y_player + 0.5;
}

void	direction_begin(t_map *data)
{
	int	player;

	player = data->x_player;
	data->x_player = data->y_player;
	data->y_player = player;
	if (data->map[data->y_player][data->x_player] == 'N')
	{
		data->diry = 1;
		data->dirx = 0;
		data->planex = 0.66;
		data->planey = 0;
	}
	else if (data->map[data->y_player][data->x_player] == 'S')
	{
		data->diry = -1;
		data->dirx = 0;
		data->planex = -0.66;
		data->planey = 0;
	}
	init_direction(data);
}
