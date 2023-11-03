#include "cub3d.h"

void	init_map(t_map *data)
{
	data->map = NULL;
    data->nb_player = 0;
    data->first_row = 0;
    data->nb_col = 0;
    data->nb_line = 0;
    data->path_N = NULL;
    data->path_S = NULL;
    data->path_E = NULL;    
    data->path_W = NULL;
    data->C_color = NULL;
    data->F_color = NULL;
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
    printf("test_rows = %d\n", test_rows(&data));
    printf("test_cols = %d\n", test_cols(&data));
	free_tab(data.map);
	return (0);
}

