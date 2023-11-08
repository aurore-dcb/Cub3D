#include "cub3d.h"

#define PI 3.14159265358979323846

int	key_hook(int keycode, t_map *data)
{
	// printf("keycode : %d\n", keycode);
	if (keycode == XK_Escape)
		mlx_loop_end(data->mlx_ptr);
	if (keycode == 97) // A
	{
		// printf("keycode : %d\n", keycode);
		data->posX -= 0.1;
	}
	else if (keycode == 119) // W
	{
		// printf("keycode : %d\n", keycode);
		data->posY -= 0.1;
	}
	else if (keycode == 100) // D	
	{
		// printf("keycode : %d\n", keycode);
		data->posX += 0.1;
	}
	else if (keycode == 115) // S
	{
		// printf("keycode : %d\n", keycode);
		data->posY += 0.1;
	}
	if (keycode == 65361) // fleche gauche
	{
		printf("data->dirX : %f   -   data->dirY : %f\n", data->dirX, data->dirY);
		printf("data->planeX : %f   -   data->planeY : %f\n", data->planeX, data->planeY);
		printf("data->alpha : %f\n", data->alpha);
		//changer l'angle
		data->alpha += 45;
		//le convertir en radian
		double rad = (data->alpha * PI) / 180;
		// printf("alpha : %f\n", rad);
		//determiner sin;
		data->dirY = sin(rad);
		// printf("sin : %f\n", data->dirY);
		//determiner cos
		data->dirX = cos(rad);
		// printf("cos : %f\n", data->dirX);

		// orienter plane
		// data->planeX = cos(rad) * 0.66;
		// data->planeY = sin(rad) * 0.66;
		// double pY = data->planeY;
		// printf("pX : %f\n", pX);
		double pY = data->planeY;
		data->planeY = data->planeX * cos(rad) - data->planeY * sin(rad);
		data->planeX = pY * sin(rad) + data->planeY * cos(rad);

		// data->planeY = data->planeY * cos(rad) - data->planeX * sin(rad);
		// // printf("pX : %f\n", pX);
		// data->planeX = pY * sin(rad) + data->planeX * cos(rad);
		
		printf("data->dirX : %f   -   data->dirY : %f\n", data->dirX, data->dirY);
		printf("data->planeX : %f   -   data->planeY : %f\n", data->planeX, data->planeY);
		// data->dirX = fmod(data->dirX - 1, 2);
		// data->dirY = fmod(data->dirY - 1, 2);
		// data->planeY -= 0.5;
		// data->planeX = data->planeX * cos(data->planeY);
		// data->planeX = fmod(data->planeX - 1, 2);
		// data->planeY = fmod(data->planeY - 1, 2);
	}
	else if (keycode == 65363) // fleche droite
	{
		data->dirY -= 0.5;
		data->dirX = data->dirX * cos(data->dirY);
		// data->dirX = fmod(data->dirX - 1, 2);
		// data->dirY = fmod(data->dirY - 1, 2);
		data->planeY -= 0.5;
		data->planeX = data->planeX * cos(data->planeY);
		// data->planeX = fmod(data->planeX - 1, 2);
		// data->planeY = fmod(data->planeY - 1, 2);
	}
	// else if (keycode == 65363) // fleche droite
	if (keycode == 97 || keycode == 119 || keycode == 100 || keycode == 115 || keycode == 65361)
	{
		mlx_clear_window(data->mlx_ptr, data->win_ptr);
		display(data);
	}
	return (1);
}