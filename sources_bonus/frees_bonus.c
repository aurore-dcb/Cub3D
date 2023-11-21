/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 13:23:04 by aducobu           #+#    #+#             */
/*   Updated: 2023/11/21 13:55:44 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	free_sprite(t_map *data)
{
	if (data->sprite.sprite)
		free(data->sprite.sprite);
	if (data->sprite.z_buffer)
		free(data->sprite.z_buffer);
	if (data->sprite.sprite_order)
		free(data->sprite.sprite_order);
	if (data->sprite.sprite_dist)
		free(data->sprite.sprite_dist);
	if (data->path_co)
		free(data->path_co);
}

void	free_all2(t_map *data)
{
	if (data->path_n)
		free(data->path_n);
	if (data->path_s)
		free(data->path_s);
	if (data->path_e)
		free(data->path_e);
	if (data->path_w)
		free(data->path_w);
	if (data->path_d)
		free(data->path_d);
	if (data->c_color)
		free(data->c_color);
	if (data->f_color)
		free(data->f_color);
}

void	free_all(t_map *data)
{
	if (data->mlx_ptr)
	{
		if (data->main.img)
			mlx_destroy_image(data->mlx_ptr, data->main.img);
		if (data->win_ptr)
			mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	free_all2(data);
	if (data->map)
		free_tab(data->map);
	if (data->tex)
		free_tab_int(data->tex, data, data->len_tex);
	free_sprite(data);
}
