#include "cub3d.h"

int	key_hook(int keycode, t_map *data)
{
	if (keycode == XK_Escape)
		mlx_loop_end(data->mlx_ptr);
	if (keycode == 123)
	{
		printf("gauche\n");
		data->posX -= 0.5;
	}
	return (1);
}