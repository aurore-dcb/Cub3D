#include "cub3d.h"

int	key_hook(int keycode, t_map *data)
{
	if (keycode == XK_Escape)
		mlx_loop_end(data->mlx_ptr);
	// else if (keycode == XK_w || keycode == XK_s || keycode == XK_a
	// 	|| keycode == XK_d)
	// {
	// 	if (modif_pos(keycode, data))
	// 		display_map(data);
	// 	if (data->map[data->pos_x][data->pos_y] == 'C')
	// 		data->map[data->pos_x][data->pos_y] = '0';
	// }
	return (1);
}