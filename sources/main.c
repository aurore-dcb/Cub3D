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

void display_map(char **map)
{
	int i = 0;
	int j;

	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			printf("%c", map[i][j]);
			j++;
		}
		i++;
		// printf("\n");
	}
}

void	init_map(t_map *data)
{
    ft_memset(data, 0, sizeof(t_map));
	data->x_player = -1;
	data->y_player = -1;
    data->width = 800;
    data->height = 600;
	data->planeX = 0;
	data->planeY = 0.66;
}

void loop(t_map *data)
{
    data->mlx_ptr = mlx_init();
    if (!data->mlx_ptr)
    {
        printf("Error\nCannot init window\n");
        return ;
    }
    data->win_ptr = mlx_new_window(data->mlx_ptr, data->width, data->height,
		"Cub3D");
    if (!data->win_ptr)
		return (ft_printf("Error\nCannot display window\n"), free(data->win_ptr));
    //charger les images
	
	//affichage
	display(data);
	//gerer les touches
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, key_hook, data);
	mlx_hook(data->win_ptr, 17, 1L << 17, mlx_loop_end, data->mlx_ptr);
	mlx_loop(data->mlx_ptr);
}

int main(int argc, char **argv, char **env)
{
	t_map	data;

	init_map(&data);
	if (!ft_parsing(argc, argv, env, &data))
		return (free_data(&data), 1);
	if (!get_map(&data, argv[1]))
		return (free_data(&data), 1);
	if (!check_map(&data))
		return (printf("Error map\n"), free_data(&data), 1);
	//afficher la map
	// display_map(data.map);
	//determiner les coordonnees du vecteur direction au debut
	coor_direction_begin(&data);
	// boucle d'affiche de la fenetre
	loop(&data);
    free_mlx(&data);
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
