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
    data->mlx_ptr = NULL;
    data->win_ptr = NULL;
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
    printf("test_cols_beg = %d\n", test_cols_beg(&data));
    printf("test_cols_end = %d\n", test_cols_end(&data));
    printf("test_empty = %d\n", test_empty(&data));
    printf("test_invalid_char = %d\n", test_invalid_char(&data));
    printf("x_player = %d y_player = %d\n", data.x_player, data.y_player);
    printf("test_player = %d\n", test_player(&data));
    // AFFICHER LA FENETRE
	free_tab(data.map);
    free_data(&data);
	return (0);
}



