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

void	free_tab_int(int **buf, t_map *data, int n)
{
	int	i;

	i = 0;
	if (!buf)
		return ;
	(void)data;
	while (i < n)
	{
		free(buf[i]);
		i++;
	}
	free(buf);
	buf = NULL;
}

void	free_buffer(unsigned int **buf, t_map *data)
{
	int	i;

	i = 0;
	if (!buf)
		return ;
	while (i < data->height && buf && buf[i] != NULL)
	{
		free(buf[i]);
		i++;
	}
	free(buf);
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
	if (data->path_n)
		free(data->path_n);
	if (data->path_s)
		free(data->path_s);
	if (data->path_e)
		free(data->path_e);
	if (data->path_w)
		free(data->path_w);
	if (data->c_color)
		free(data->c_color);
	if (data->f_color)
		free(data->f_color);
	if (data->map)
		free_tab(data->map);
	if (data->tex)
		free_tab_int(data->tex, data, data->len_tex);
}
