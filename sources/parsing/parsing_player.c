#include "cub3d.h"

int	test_player(t_map *data)
{
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