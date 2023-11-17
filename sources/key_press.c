#include "cub3d.h"

void	left_key(t_map *data)
{
	double	rad;
	double	dx;
	double	px;

	dx = data->dirx;
	px = data->planex;
	rad = (ALPHA * PI) / 180;
	data->dirx = data->dirx * cos(rad) - data->diry * sin(rad);
	data->diry = dx * sin(rad) + data->diry * cos(rad);
	data->planex = data->planex * cos(rad) - data->planey * sin(rad);
	data->planey = px * sin(rad) + data->planey * cos(rad);
}

void	right_key(t_map *data)
{
	double	rad;
	double	dx;
	double	px;

	dx = data->dirx;
	px = data->planex;
	rad = (-ALPHA * PI) / 180;
	data->dirx = data->dirx * cos(rad) - data->diry * sin(rad);
	data->diry = dx * sin(rad) + data->diry * cos(rad);
	data->planex = data->planex * cos(rad) - data->planey * sin(rad);
	data->planey = px * sin(rad) + data->planey * cos(rad);
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
