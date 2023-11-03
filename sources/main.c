#include "cub3d.h"

void	init_map(t_map *data)
{
	data->map = NULL;
	data->nb_player = 0;
	data->nb_col = 0;
	data->nb_line = 0;
	data->x_player = -1;
	data->y_player = -1;
	data->path_N = NULL;
	data->path_S = NULL;
	data->path_E = NULL;
	data->path_W = NULL;
	data->C_color = NULL;
	data->F_color = NULL;
}

int	main(int argc, char **argv, char **env)
{
	t_map	data;

	init_map(&data);
	if (!ft_parsing(argc, argv, env, &data))
		return (1);
	if (!get_map(&data, argv[1]))
		return (free_data(&data), 1);
	if (!check_map(&data))
		return (printf("Error map\n"), free_data(&data), 1);
	free_data(&data);
	return (0);
}
