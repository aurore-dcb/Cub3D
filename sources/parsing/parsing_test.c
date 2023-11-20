/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmeriau <rmeriau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:00:45 by rmeriau           #+#    #+#             */
/*   Updated: 2023/11/20 11:57:32 by rmeriau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	test_cols_beg(t_map *data)
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
			while (is_sp(data->map[i][j]))
				j++;
			if (data->map[i][j] && data->map[i][j] != '1')
				return (0);
			i++;
		}
	}
	return (1);
}

int	test_cols_end(t_map *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < data->nb_line)
	{
		j = 0;
		if (ft_strlen(data->map[i]) > 1)
		{
			while (data->map[i][j])
				j++;
			j--;
			while (j > 0 && is_sp(data->map[i][j]))
				j--;
			if (data->map[i][j] && data->map[i][j] != '1')
				return (0);
		}
		i++;
	}
	return (1);
}

int	do_test_empty(t_map *data, int i)
{
	int	j;

	j = 0;
	if (ft_strlen(data->map[i]))
	{
		while (data->map[i][j + 1])
		{
			if (data->map[i][j] == '0')
				if ((ft_strlen(data->map[i - 1]) < j)
					|| !data->map[i - 1][j] || is_sp(data->map[i - 1][j]))
					return (0);
			if (data->map[i][j] == '0')
				if ((ft_strlen(data->map[i + 1]) < j)
					|| !data->map[i + 1][j] || is_sp(data->map[i + 1][j]))
					return (0);
			if (data->map[i][j] == '0'
				&& (!data->map[i][j + 1] || is_sp(data->map[i][j + 1])))
				return (0);
			if (data->map[i][j] == '0'
				&& (!data->map[i][j - 1] || is_sp(data->map[i][j - 1])))
				return (0);
			j++;
		}
	}
	return (1);
}

int	test_empty(t_map *data)
{
	int	i;

	i = 1;
	if (data->map)
	{
		while (i < data->nb_line - 1)
		{
			if (!do_test_empty(data, i))
				return (0);
			i++;
		}
	}
	return (1);
}
