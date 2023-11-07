#include "cub3d.h"

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
	// if (keycode == 65361) // fleche gauche
	// {
	// 	data->dirX = fabs(data->dirX - 1);
	// 	data->dirY = fabs(data->dirY - 1);
	// }
	// else if (keycode == 65363) // fleche droite
	if (keycode == 97 || keycode == 119 || keycode == 100 || keycode == 115 || keycode == 65361)
	{
		mlx_clear_window(data->mlx_ptr, data->win_ptr);
		display(data);
	}
	return (1);
}