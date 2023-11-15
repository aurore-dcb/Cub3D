#include "cub3d_bonus.h"

void	mouse_y(t_map *data, int last, int y)
{
	double	old_dir_y;
	double	old_plane_y;
	double	delta_y;

	delta_y = -(y - last) * 0.005;
	old_dir_y = data->dirY;
	data->dirY = data->dirY * cos(delta_y) - data->dirX * sin(delta_y);
	data->dirX = old_dir_y * sin(delta_y) + data->dirX * cos(delta_y);
	old_plane_y = data->planeY;
	data->planeY = data->planeY * cos(delta_y) - data->planeX * sin(delta_y);
	data->planeX = old_plane_y * sin(delta_y) + data->planeX * cos(delta_y);
}

void	mouse_x(t_map *data, int last, int x)
{
	double	delta_x;
	double	old_dir_x;
	double	old_plane_x;

	delta_x = -(x - last) * 0.005;
	old_dir_x = data->dirX;
	data->dirX = data->dirX * cos(delta_x) - data->dirY * sin(delta_x);
	data->dirY = old_dir_x * sin(delta_x) + data->dirY * cos(delta_x);
	old_plane_x = data->planeX;
	data->planeX = data->planeX * cos(delta_x) - data->planeY * sin(delta_x);
	data->planeY = old_plane_x * sin(delta_x) + data->planeY * cos(delta_x);
}

int	mouse_move(int x, int y, t_map *data)
{
	static int	last_x;
	static int	last_y;

	if (last_x == 0)
	{
		last_x = -1;
		last_y = -1;
	}
	if (last_x != -1 && last_y != -1)
	{
		mouse_y(data, last_y, y);
		mouse_x(data, last_x, x);
	}
	last_x = x;
	last_y = y;
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	display(data);
	return (0);
}
