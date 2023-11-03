#include "cub3d.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void free_data(t_map *data)
{   
	if (data->path_N)
    	free(data->path_N);
    free(data->path_S);
    free(data->path_E);    
    free(data->path_W);
    free(data->C_color);
    free(data->F_color);
}

void free_mlx(t_map *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
    mlx_destroy_display(data->mlx_ptr);
    free(data->mlx_ptr);
}

void	free_char_spe(char **tableau, int len)
{
	int	i;

	i = 0;
	if (tableau == NULL)
		return ;
	while (i < len)
	{
		free(tableau[i]);
		i++;
	}
	free(tableau);
}