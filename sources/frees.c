#include "cub3d.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void free_data(t_map *data)
{   
    free(data->path_N);
    free(data->path_S);
    free(data->path_E);    
    free(data->path_W);
    free(data->C_color);
    free(data->F_color);
}
