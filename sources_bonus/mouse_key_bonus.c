#include "cub3d_bonus.h"

void	mouse_y(t_map *data)
{
	double	old_dir_y;
	double	old_plane_y;
	double	rad;

	rad = (ALPHA_MOUSE * PI) / 180;
	old_dir_y = data->dirY;
	data->dirY = data->dirY * cos(rad) - data->dirX * sin(rad);
	data->dirX = old_dir_y * sin(rad) + data->dirX * cos(rad);
	old_plane_y = data->planeY;
	data->planeY = data->planeY * cos(rad) - data->planeX * sin(rad);
	data->planeX = old_plane_y * sin(rad) + data->planeX * cos(rad);
}

void	mouse_x(t_map *data)
{
	double	rad;
	double	old_dir_x;
	double	old_plane_x;

	rad = (ALPHA_MOUSE * PI) / 180;
	old_dir_x = data->dirX;
	data->dirX = data->dirX * cos(rad) - data->dirY * sin(rad);
	data->dirY = old_dir_x * sin(rad) + data->dirY * cos(rad);
	old_plane_x = data->planeX;
	data->planeX = data->planeX * cos(rad) - data->planeY * sin(rad);
	data->planeY = old_plane_x * sin(rad) + data->planeY * cos(rad);
}

int	mouse_move(int x, int y, t_map *data)
{
	if (data->b_left == 1)
	{
		mlx_mouse_move(data->mlx_ptr, data->win_ptr, data->width / 2,
			data->height / 2);
	}
	data->mx = x;
	(void)y;
	return (0);
}

int	mouse_click(int button, int x, int y, t_map *data)
{
	(void)x;
	(void)y;
	if (button == 1)
	{
		mlx_mouse_move(data->mlx_ptr, data->win_ptr, data->width / 2,
			data->height / 2);
		data->b_left *= -1;
	}
	return (0);
}
