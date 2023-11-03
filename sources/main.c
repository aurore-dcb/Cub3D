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
// 	free_tab(data.map);
// 	return (0);
// }


int main(int argc, char **argv, char **env)
{
    t_map data;

    init_map(&data);
    if (!ft_parsing(argc, argv, env, &data))
        return (free_data(&data), 1);
    printf("path N = %s\n", data.path_N);
    printf("path S = %s\n", data.path_S);
    printf("path E = %s\n", data.path_E);
    printf("path W = %s\n", data.path_W);
    printf("color C = %s\n", data.C_color);
    printf("color F = %s\n", data.F_color);
    free_data(&data);
    return (0);
}
