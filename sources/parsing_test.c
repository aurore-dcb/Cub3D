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
		while (data->map[i][j])
			j++;
		j--;
		while (is_sp(data->map[i][j]))
			j--;
		if (data->map[i][j] && data->map[i][j] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	test_empty(t_map *data)
{
	int	i;
	int	j;

	i = 1;
	j = 1;
	if (data->map)
	{
		while (i < data->nb_line - 1)
		{
			j = 0;
			while (data->map[i][j + 1])
			{
				if ((data->map[i][j] == '0' && is_sp(data->map[i - 1][j]))
					|| (data->map[i][j] == '0' && is_sp(data->map[i + 1][j]))
					|| (data->map[i][j] == '0' && is_sp(data->map[i][j + 1]))
					|| (data->map[i][j] == '0' && is_sp(data->map[i][j - 1])))
					return (0);
				j++;
			}
			i++;
		}
	}
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

int	test_player(t_map *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (data->nb_player != 1)
		return (0);
	if (data->map[data->x_player + 1][data->y_player]
		&& is_sp(data->map[data->x_player + 1][data->y_player]))
		return (0);
	else if (data->map[data->x_player - 1][data->y_player]
		&& is_sp(data->map[data->x_player - 1][data->y_player]))
		return (0);
	else if (data->map[data->x_player][data->y_player + 1]
		&& is_sp(data->map[data->x_player][data->y_player + 1]))
		return (0);
	else if (data->map[data->x_player][data->y_player - 1]
		&& is_sp(data->map[data->x_player][data->y_player - 1]))
		return (0);
	return (1);
}
