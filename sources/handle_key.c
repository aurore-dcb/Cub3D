/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmeriau <rmeriau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:01:17 by rmeriau           #+#    #+#             */
/*   Updated: 2023/11/20 11:01:18 by rmeriau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	w_key(t_map *data)
{
	char		new_posx;
	char		new_posy;

	new_posx = data->map[(int)(data->posy)][(int)(data->posx + data->dirx
			* (data->speed + 0.0001))];
	new_posy = data->map[(int)(data->posy - data->diry
			* (data->speed + 0.0001))][(int)(data->posx)];
	if (new_posx != '1')
		data->posx += data->speed * data->dirx;
	if (new_posy != '1')
		data->posy -= data->speed * data->diry;
}

void	s_key(t_map *data)
{
	char		new_posx;
	char		new_posy;

	new_posx = data->map[(int)(data->posy)][(int)(data->posx - data->dirx
			* (data->speed + 0.0001))];
	new_posy = data->map[(int)(data->posy + data->diry
			* (data->speed + 0.0001))][(int)(data->posx)];
	if (new_posx != '1')
		data->posx -= data->speed * data->dirx;
	if (new_posy != '1')
		data->posy += data->speed * data->diry;
}

void	a_key(t_map *data)
{
	char		new_posx;
	char		new_posy;

	new_posx = data->map[(int)(data->posy)][(int)(data->posx - data->planex
			* (data->speed + 0.0001))];
	new_posy = data->map[(int)(data->posy + data->planey
			* (data->speed + 0.0001))][(int)(data->posx)];
	if (new_posx != '1')
		data->posx -= data->speed * data->planex;
	if (new_posy != '1')
		data->posy += data->speed * data->planey;
}

void	d_key(t_map *data)
{
	char		new_posx;
	char		new_posy;

	new_posx = data->map[(int)(data->posy)][(int)(data->posx + data->planex
			* (data->speed + 0.0001))];
	new_posy = data->map[(int)(data->posy - data->planey
			* (data->speed + 0.0001))][(int)(data->posx)];
	if (new_posx != '1')
		data->posx += data->speed * data->planex;
	if (new_posy != '1')
		data->posy -= data->speed * data->planey;
}
