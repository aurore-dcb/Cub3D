#include "cub3d.h"

int	good_keycode(int keycode)
{
	return (keycode == 97 || keycode == 119 || keycode == 100 || keycode == 115
		|| keycode == 65361 || keycode == 65363 || keycode == 109);
}

void	left_key(t_map *data)
{
	double	rad;
	double	dx;
	double	px;

	dx = data->dirX;
	px = data->planeX;
	rad = (ALPHA * PI) / 180;
	data->dirX = data->dirX * cos(rad) - data->dirY * sin(rad);
	data->dirY = dx * sin(rad) + data->dirY * cos(rad);
	data->planeX = data->planeX * cos(rad) - data->planeY * sin(rad);
	data->planeY = px * sin(rad) + data->planeY * cos(rad);
}

void	right_key(t_map *data)
{
	double	rad;
	double	dx;
	double	px;

	dx = data->dirX;
	px = data->planeX;
	rad = (-ALPHA * PI) / 180;
	data->dirX = data->dirX * cos(rad) - data->dirY * sin(rad);
	data->dirY = dx * sin(rad) + data->dirY * cos(rad);
	data->planeX = data->planeX * cos(rad) - data->planeY * sin(rad);
	data->planeY = px * sin(rad) + data->planeY * cos(rad);
}

int	key_hook(int keycode, t_map *data)
{
	if (keycode == XK_Escape)
		mlx_loop_end(data->mlx_ptr);
	if (keycode == 119)
		w_key(data);
	else if (keycode == 115)
		s_key(data);
	else if (keycode == 97)
		a_key(data);
	else if (keycode == 100)
		d_key(data);
	if (keycode == 65361)
		left_key(data);
	else if (keycode == 65363)
		right_key(data);
	if (keycode == 109)
		data->dis_map = (data->dis_map + 1) % 2;
	if (good_keycode(keycode) == 1)
	{
		mlx_clear_window(data->mlx_ptr, data->win_ptr);
		display(data);
	}
	return (1);
}
