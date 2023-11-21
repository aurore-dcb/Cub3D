/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 13:22:54 by aducobu           #+#    #+#             */
/*   Updated: 2023/11/21 13:45:37 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	fill_sprite(t_map *data)
{
	int	x;
	int	y;
	int	i;

	y = 0;
	i = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == 'C')
			{
				data->sprite.sprite[i].x = (double)(x) + 0.5;
				data->sprite.sprite[i].y = (double)(y) + 0.5;
				data->sprite.sprite[i++].texture = 5;
			}
			x += 1;
		}
		y += 1;
	}
}

int	init_sprite(t_map *data)
{
	data->sprite.sprite = malloc(sizeof(t_sprite) * nb_sprite(data));
	if (!data->sprite.sprite)
		return (printf("Error\nMalloc sprites\n"), 0);
	fill_sprite(data);
	if (!data->sprite.z_buffer)
	{
		data->sprite.z_buffer = malloc(sizeof(double) * data->width);
		if (!data->sprite.z_buffer)
			return (printf("Error\nMalloc sprites\n"), 0);
	}
	data->sprite.sprite_order = malloc(sizeof(int) * nb_sprite(data));
	if (!data->sprite.sprite_order)
		return (printf("Error\nMalloc sprites\n"), 0);
	data->sprite.sprite_dist = malloc(sizeof(double) * nb_sprite(data));
	if (!data->sprite.sprite_dist)
		return (printf("Error\nMalloc sprites\n"), 0);
	data->nb_sprites = nb_sprite(data);
	return (1);
}

int	nb_sprite(t_map *data)
{
	int	x;
	int	y;
	int	nb;

	y = 0;
	nb = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == 'C')
				nb++;
			x++;
		}
		y++;
	}
	return (nb);
}

void	sort_order(t_pair *orders, int nb)
{
	int		i;
	int		j;
	t_pair	tmp;

	i = -1;
	j = -1;
	while (++i < nb)
	{
		while (++j < nb - 1)
		{
			if (orders[j].first > orders[j + 1].first)
			{
				tmp.first = orders[j].first;
				tmp.second = orders[j].second;
				orders[j].first = orders[j + 1].first;
				orders[j].second = orders[j + 1].second;
				orders[j + 1].first = tmp.first;
				orders[j + 1].second = tmp.second;
			}
		}
	}
}

void	sort_sprites(int *order, double *dist, int nb)
{
	int		i;
	t_pair	*sprites;

	i = -1;
	sprites = malloc(sizeof(t_pair) * nb);
	if (!sprites)
		return ;
	while (++i < nb)
	{
		sprites[i].first = dist[i];
		sprites[i].second = order[i];
	}
	sort_order(sprites, nb);
	i = -1;
	while (++i < nb)
	{
		dist[i] = sprites[nb - i - 1].first;
		order[i] = sprites[nb - i - 1].second;
	}
	free(sprites);
}
