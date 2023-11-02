#include "cub3d.h"

void init_data(t_map *data)
{   
    data->path_N = NULL;
    data->path_S = NULL;
    data->path_E = NULL;    
    data->path_W = NULL;
    data->C_color = NULL;
    data->F_color = NULL;
}

int main(int argc, char **argv, char **env)
{
    t_map data;

    init_data(&data);
    if (!ft_parsing(argc, argv, env, &data))
        return (1);
    printf("path N = %s\n", data.path_N);
    printf("path S = %s\n", data.path_S);
    printf("path E = %s\n", data.path_E);
    printf("path W = %s\n", data.path_W);
    printf("color C = %s\n", data.C_color);
    printf("color F = %s\n", data.F_color);
    free_data(&data);
    return (0);
}