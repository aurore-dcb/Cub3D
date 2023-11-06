#include "cub3d.h"

// int	main(int argc, char **argv, char **env)
// {
//     t_map data;
//     (void)argc;
// 	(void)argv;
// 	(void)env;

// 	init_map(&data);
// 	if (!read_file(&data, "./maps/cub.map"))
// 		return (1);
// 	printf("line = %d col = %d\n", data.nb_line, data.nb_col);
// 	if (!get_map(&data, "./maps/cub.map"))
// 		return (1);
// 	int i = 0;
// 	while (data.map[i])
// 	{
// 		printf("%s", data.map[i]);
// 		i++;
// 	}
//     printf("test_rows = %d\n", test_rows(&data));
//     printf("test_cols_beg = %d\n", test_cols_beg(&data));
//     printf("test_cols_end = %d\n", test_cols_end(&data));
//     printf("test_empty = %d\n", test_empty(&data));
//     printf("test_invalid_char = %d\n", test_invalid_char(&data));
//     printf("x_player = %d y_player = %d\n", data.x_player, data.y_player);
//     printf("test_player = %d\n", test_player(&data));
    
// 	free_tab(data.map);
//     free_data(&data);
// 	return (0);
// }

void	init_map(t_map *data)
{
    ft_memset(data, 0, sizeof(t_map));
	data->x_player = -1;
	data->y_player = -1;
    data->width = 320;
    data->height = 200;
}

void loop(t_map *data)
{
    data->mlx_ptr = mlx_init();
    if (!data->mlx_ptr)
    {
        printf("Error\nCannot init window\n");
        return ;
    }
    printf("OK\n");
    data->win_ptr = mlx_new_window(data->mlx_ptr, data->width, data->height,
		"Cub3D");
    if (!data->win_ptr)
		return (ft_printf("Error\n"), free(data->win_ptr));
    mlx_loop(data->mlx_ptr);
    
}

int main(int argc, char **argv, char **env)
{
	t_map	data;

	init_map(&data);
	if (!ft_parsing(argc, argv, env, &data))
		return (1);
	if (!get_map(&data, argv[1]))
		return (free_data(&data), 1);
	// int i = 0;
	// while (data.map[i])
	// {
	// 	printf("%s\n", data.map[i]);
	// 	i++;
	// }
	if (!check_map(&data))
		return (free_data(&data), 1);
	free_data(&data);
	return (0);
}

// int main(int argc, char **argv, char **env)
// {
//     t_map data;

//     init_map(&data);
//     if (!ft_parsing(argc, argv, env, &data))
//         return (free_data(&data), 1);
//     printf("path N = %s\n", data.path_N);
//     printf("path S = %s\n", data.path_S);
//     printf("path E = %s\n", data.path_E);
//     printf("path W = %s\n", data.path_W);
//     printf("color C = %s\n", data.C_color);
//     printf("color F = %s\n", data.F_color);
//     // AFFICHER LA FENETRE
//     loop(&data);
//     free_data(&data);
//     free_mlx(&data);
//     return (0);
// }
