#include "cub3d.h"

int	key_hook(int keycode, t_map *data)
{
	if (keycode == XK_Escape)
		mlx_loop_end(data->mlx_ptr);
	if (keycode == 65361) // fleche gauche
	{
		printf("keycode : %d\n", keycode);
		data->posX -= 0.1;
	}
	else if (keycode == 65362) // fleche haut
	{
		printf("keycode : %d\n", keycode);
		data->posY -= 0.1;
	}
	else if (keycode == 65363) // fleche droite	
	{
		printf("keycode : %d\n", keycode);
		data->posX += 0.1;
	}
	else if (keycode == 65364) // fleche bas
	{
		printf("keycode : %d\n", keycode);
		data->posY += 0.1;
	}
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	display(data);
	return (1);
}