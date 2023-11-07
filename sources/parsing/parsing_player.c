#include "cub3d.h"

int	test_player(t_map *data)
{
	if (data->nb_player != 1)
		return (0);
	if (!data->map[data->x_player + 1][data->y_player]
		|| !data->map[data->x_player - 1][data->y_player]
		|| !data->map[data->x_player][data->y_player + 1]
		|| !data->map[data->x_player][data->y_player - 1])
		return (0);
	if (is_sp(data->map[data->x_player + 1][data->y_player]))
		return (0);
	else if (is_sp(data->map[data->x_player - 1][data->y_player]))
		return (0);
	else if (is_sp(data->map[data->x_player][data->y_player + 1]))
		return (0);
	else if (is_sp(data->map[data->x_player][data->y_player - 1]))
		return (0);
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
				if (data->map[i][j] && !test_valid_carac(data->map[i][j]))
					return (0);
				j++;
			}
			i++;
		}
	}
	return (1);
}

int	do_beg_parse_map(t_map *data, int i, int *empty_line)
{
	int	j;

	j = 0;
	if (!data->map[i][0])
	{
		*empty_line = 1;
		return (0);
	}
	while (is_sp(data->map[i][j]))
		j++;
	if (j == ft_strlen(data->map[i]))
	{
		*empty_line = 1;
		return (0);
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
	int	j;
	int	empty_line;

	i = 0;
	j = 0;
	empty_line = 0;
	while (i < data->nb_line)
	{
		if (!do_beg_parse_map(data, i, &empty_line))
			break ;
		i++;
	}
	i++;
	if (!do_end_parse_map(data, i, empty_line))
		return (0);
	return (1);
}