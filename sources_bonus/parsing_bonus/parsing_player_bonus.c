/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_player_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 13:22:18 by aducobu           #+#    #+#             */
/*   Updated: 2023/11/21 13:22:19 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	test_rows(t_map *data)
{
	int	i;

	i = 0;
	if (data->map[0])
	{
		while (data->map[0][i])
		{
			if (data->map[0][i] != '1' && !is_sp(data->map[0][i]))
				return (0);
			i++;
		}
	}
	i = 0;
	if (data->map[data->nb_line - 1])
	{
		while (data->map[data->nb_line - 1][i])
		{
			if (data->map[data->nb_line - 1][i] != '1'
				&& !is_sp(data->map[data->nb_line - 1][i]))
				return (0);
			i++;
		}
	}
	return (1);
}

int	test_player(t_map *data)
{
	if (data->nb_player != 1)
		return (printf("Error\nWrong number of player\n"), 0);
	if (!data->map[data->x_player + 1][data->y_player]
		|| !data->map[data->x_player - 1][data->y_player]
		|| !data->map[data->x_player][data->y_player + 1]
		|| !data->map[data->x_player][data->y_player - 1])
		return (printf("Error\nNeeded wall\n"), 0);
	if (is_sp(data->map[data->x_player + 1][data->y_player]))
		return (printf("Error\nNeeded wall\n"), 0);
	else if (is_sp(data->map[data->x_player - 1][data->y_player]))
		return (printf("Error\nNeeded wall\n"), 0);
	else if (is_sp(data->map[data->x_player][data->y_player + 1]))
		return (printf("Error\nNeeded wall\n"), 0);
	else if (is_sp(data->map[data->x_player][data->y_player - 1]))
		return (printf("Error\nNeeded wall\n"), 0);
	return (1);
}

int	test_invalid_char(t_map *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (data->map)
	{
		while (i < data->nb_line)
		{
			j = 0;
			while (data->map[i][j])
			{
				if (data->map[i][j] && !test_valid_carac(data->map[i][j], data))
					return (0);
				if (data->map[i][j] && data->map[i][j] == 'D')
					data->nb_doors += 1;
				if (data->map[i][j] && data->map[i][j] == 'C')
					data->nb_sprites += 1;
				j++;
			}
			i++;
		}
	}
	return (1);
}

int	do_end_parse_map(t_map *data, int i, int empty_line)
{
	int	j;

	j = 0;
	if (empty_line)
	{
		while (i < data->nb_line)
		{
			j = 0;
			while (is_sp(data->map[i][j]))
				j++;
			if (data->map[i][j] && data->map[i][j] == '1')
				return (0);
			i++;
		}
	}
	return (1);
}

int	beg_parse_map(t_map *data)
{
	int	i;
	int	empty_line;

	i = 0;
	empty_line = 0;
	while (i < data->nb_line)
	{
		if (data->map[i][0] == '\n')
		{
			empty_line = 1;
			break ;
		}
		i++;
	}
	i++;
	if (!do_end_parse_map(data, i, empty_line))
		return (0);
	return (1);
}
