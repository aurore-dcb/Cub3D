#include "cub3d.h"

void	init_map(t_map *data)
{
	data->map = NULL;
    data->nb_player = 0;
    data->first_row = 0;
    data->nb_col = 0;
    data->nb_line = 0;
}

int	main(int argc, char **argv, char **env)
{
    t_map data;
    (void)argc;
	(void)argv;
	(void)env;

	init_map(&data);
	if (!read_file(&data, "./maps/cub.map"))
		return (1);
	printf("line = %d col = %d\n", data.nb_line, data.nb_col);
	if (!get_map(&data, "./maps/cub.map"))
		return (1);
	int i = 0;
	while (data.map[i])
	{
		printf("%s", data.map[i]);
		i++;
	}
	free_char(data.map);
	return (0);
}
