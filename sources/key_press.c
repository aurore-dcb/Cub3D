#include "cub3d.h"

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

int	key_press(int keycode, t_map *data)
{
	if (keycode == 119)
		data->w = 1;
	else if (keycode == 115)
		data->s = 1;
	else if (keycode == 100)
		data->d = 1;
	else if (keycode == 97)
		data->a = 1;
	else if (keycode == 65363)
		data->right = 1;
	else if (keycode == 65361)
		data->left = 1;
	else if (keycode == XK_Escape)
		mlx_loop_end(data->mlx_ptr);
	return (0);
}

int	key_release(int keycode, t_map *data)
{
	if (keycode == 119)
		data->w = 0;
	else if (keycode == 115)
		data->s = 0;
	else if (keycode == 100)
		data->d = 0;
	else if (keycode == 97)
		data->a = 0;
	else if (keycode == 65363)
		data->right = 0;
	else if (keycode == 65361)
		data->left = 0;
	return (0);
}

int	key_hook(t_map *data)
{
	data->speed = 0.01;
	if (data->w)
		w_key(data);
	if (data->s)
		s_key(data);
	if (data->a)
		a_key(data);
	if (data->d)
		d_key(data);
	if (data->right)
		right_key(data);
	if (data->left)
		left_key(data);
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	display(data);
	return (1);
}
