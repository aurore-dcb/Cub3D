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

void	free_data(t_map *data)
{
	if (data->map)
		free_tab(data->map);
	if (data->path_N)
		free(data->path_N);
	if (data->path_S)
		free(data->path_S);
	if (data->path_E)
		free(data->path_E);
	if (data->path_W)
		free(data->path_W);
	if (data->C_color)
		free(data->C_color);
	if (data->F_color)
		free(data->F_color);
}
