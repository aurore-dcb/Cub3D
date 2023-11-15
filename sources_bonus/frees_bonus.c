#include "cub3d_bonus.h"

void	free_all2(t_map *data)
{
	if (data->path_N)
		free(data->path_N);
	if (data->path_S)
		free(data->path_S);
	if (data->path_E)
		free(data->path_E);
	if (data->path_W)
		free(data->path_W);
	if (data->path_D)
		free(data->path_D);
	if (data->C_color)
		free(data->C_color);
	if (data->F_color)
		free(data->F_color);
}

void	free_all(t_map *data)
{
	if (data->mlx_ptr)
	{
		if (data->main.img)
			mlx_destroy_image(data->mlx_ptr, data->main.img);
		if (data->win_ptr)
			mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	free_all2(data);
	if (data->map)
		free_tab(data->map);
	if (data->tex)
		free_tab_int(data->tex, data, data->len_tex);
}
