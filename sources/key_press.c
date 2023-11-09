#include "cub3d.h"

#define PI 3.14159265358979323846

int	key_hook(int keycode, t_map *data)
{
	if (keycode == XK_Escape)
		mlx_loop_end(data->mlx_ptr);
	if (keycode == 119) // W
	{
		data->posX += 0.1 * data->dirX;
		data->posY -= 0.1 * data->dirY;
	}
	else if (keycode == 115) // S
	{
		data->posX -= 0.1 * data->dirX;
		data->posY += 0.1 * data->dirY;
	}
	else if (keycode == 97) // A
	{
		data->posX -= 0.1 * data->planeX;
		data->posY += 0.1 * data->planeY;
	}
	else if (keycode == 100) // D	
	{
		data->posX += 0.1 * data->planeX;
		data->posY -= 0.1 * data->planeY;
	}
	if (keycode == 65361) // fleche gauche
	{
		data->alpha = 2;
		double rad = (data->alpha * PI) / 180;

		double dX = data->dirX;
		data->dirX = data->dirX * cos(rad) - data->dirY * sin(rad);
		data->dirY = dX * sin(rad) + data->dirY * cos(rad);

		double pX = data->planeX;
		data->planeX = data->planeX * cos(rad) - data->planeY * sin(rad);
		data->planeY = pX * sin(rad) + data->planeY * cos(rad);
	}
	else if (keycode == 65363) // fleche droite
	{
		data->alpha = -2;
		double rad = (data->alpha * PI) / 180;

		double dX = data->dirX;
		data->dirX = data->dirX * cos(rad) - data->dirY * sin(rad);
		data->dirY = dX * sin(rad) + data->dirY * cos(rad);

		double pX = data->planeX;
		data->planeX = data->planeX * cos(rad) - data->planeY * sin(rad);
		data->planeY = pX * sin(rad) + data->planeY * cos(rad);
	}
	if (keycode == 97 || keycode == 119 || keycode == 100 || keycode == 115 || keycode == 65361 || keycode == 65363)
	{
		mlx_clear_window(data->mlx_ptr, data->win_ptr);
		display(data);
	}
	return (1);
}