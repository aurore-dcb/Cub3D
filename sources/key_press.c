#include "cub3d.h"

int	key_hook(int keycode, t_map *data)
{
	int new_posX = 0;
	int new_posY = 0;

	if (keycode == XK_Escape)
		mlx_loop_end(data->mlx_ptr);
	if (keycode == 119) // W
	{
		new_posX = data->map[(int)(data->posY)][(int)(data->posX + data->dirX * 0.1)];
		new_posY = data->map[(int)(data->posY - data->dirY * 0.1)][(int)(data->posX)];

		// dprintf(2, "x = %d y = %d case = %s", (int)(data->posY), (int)(data->posX + data->dirX * 0.1), data->map[(int)(data->posY)][(int)(data->posX + data->dirX * 0.1)]);
		if (new_posX == '0' || is_carac_map(new_posX))
			data->posX += 0.1 * data->dirX;
		if (new_posY == '0' || is_carac_map(new_posY))
			data->posY -= 0.1 * data->dirY;
	}
	else if (keycode == 115) // S
	{
		new_posX = data->map[(int)(data->posY)][(int)(data->posX - data->dirX * 0.1)];
		new_posY = data->map[(int)(data->posY + data->dirY * 0.1)][(int)(data->posX)];

		if (new_posX == '0' || is_carac_map(new_posX))
			data->posX -= 0.1 * data->dirX;
		if (new_posY == '0' || is_carac_map(new_posY))
			data->posY += 0.1 * data->dirY;
	}
	else if (keycode == 97) // A
	{
		new_posX = data->map[(int)(data->posY)][(int)(data->posX - data->planeX * 0.1)];
		new_posY = data->map[(int)(data->posY + data->planeY * 0.1)][(int)(data->posX)];
		if (new_posX == '0' || is_carac_map(new_posX))
			data->posX -= 0.1 * data->planeX;
		if (new_posY == '0' || is_carac_map(new_posY))
			data->posY += 0.1 * data->planeY;
	}
	else if (keycode == 100) // D	
	{
		new_posX = data->map[(int)(data->posY)][(int)(data->posX + data->planeX * 0.1)];
		new_posY = data->map[(int)(data->posY - data->planeY * 0.1)][(int)(data->posX)];
		if (new_posX == '0' || is_carac_map(new_posX))
			data->posX += 0.1 * data->planeX;
		if (new_posY == '0' || is_carac_map(new_posY))
			data->posY -= 0.1 * data->planeY;
	}
	if (keycode == 65361) // fleche gauche
	{
		double rad = (ALPHA * PI) / 180;

		double dX = data->dirX;
		data->dirX = data->dirX * cos(rad) - data->dirY * sin(rad);
		data->dirY = dX * sin(rad) + data->dirY * cos(rad);

		double pX = data->planeX;
		data->planeX = data->planeX * cos(rad) - data->planeY * sin(rad);
		data->planeY = pX * sin(rad) + data->planeY * cos(rad);
	}
	else if (keycode == 65363) // fleche droite
	{
		double rad = (-ALPHA * PI) / 180;

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