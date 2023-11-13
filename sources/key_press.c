#include "cub3d.h"

int    mouse_move(int x, int y, t_map *data)
{
    static int    last_x = -1;
    static int    last_y = -1;

    if (last_x != -1 && last_y != -1)
    {
        double delta_x = -(x - last_x) * 0.005;
        double delta_y = -(y - last_y) * 0.005; // Ajustez la sensibilité comme nécessaire

        // Rotation horizontale
        double old_dir_x = data->dirX;
        data->dirX = data->dirX * cos(delta_x) - data->dirY * sin(delta_x);
        data->dirY = old_dir_x * sin(delta_x) + data->dirY * cos(delta_x);

        double old_plane_x = data->planeX;
        data->planeX = data->planeX * cos(delta_x) - data->planeY * sin(delta_x);
        data->planeY = old_plane_x * sin(delta_x) + data->planeY * cos(delta_x);
        
        // // Rotation verticale
        double old_dir_y = data->dirY;
        data->dirY = data->dirY * cos(delta_y) - data->dirX * sin(delta_y);
        data->dirX = old_dir_y * sin(delta_y) + data->dirX * cos(delta_y);

        double old_plane_y = data->planeY;
        data->planeY = data->planeY * cos(delta_y) - data->planeX * sin(delta_y);
        data->planeX = old_plane_y * sin(delta_y) + data->planeX * cos(delta_y);

    }

    last_x = x;
    last_y = y;

    // Appeler la fonction de rendu ici si nécessaire
    display(data);
    return (0);
}

int good_keycode(int keycode)
{
	return (keycode == 97 || keycode == 119 || keycode == 100 || keycode == 115
		|| keycode == 65361 || keycode == 65363 || keycode == 109);
}

int	key_hook(int keycode, t_map *data)
{
	int		new_posx;
	int		new_posy;
	double	rad;
	double	dx;
	double	px;

	// printf("keycode : %d\n", keycode);
	new_posx = 0;
	new_posy = 0;
	rad = 0.0;
	dx = data->dirX;
	px = data->planeX;
	if (keycode == XK_Escape)
		mlx_loop_end(data->mlx_ptr);
	if (keycode == 119) // W
	{
		new_posx = data->map[(int)(data->posY)][(int)(data->posX + data->dirX
				* 0.1)];
		new_posy = data->map[(int)(data->posY - data->dirY
				* 0.1)][(int)(data->posX)];
		if (new_posx == '0' || is_carac_map(new_posx))
			data->posX += 0.1 * data->dirX;
		if (new_posy == '0' || is_carac_map(new_posy))
			data->posY -= 0.1 * data->dirY;
	}
	else if (keycode == 115) // S
	{
		new_posx = data->map[(int)(data->posY)][(int)(data->posX - data->dirX
				* 0.1)];
		new_posy = data->map[(int)(data->posY + data->dirY
				* 0.1)][(int)(data->posX)];
		if (new_posx == '0' || is_carac_map(new_posx))
			data->posX -= 0.1 * data->dirX;
		if (new_posy == '0' || is_carac_map(new_posy))
			data->posY += 0.1 * data->dirY;
	}
	else if (keycode == 97) // A
	{
		new_posx = data->map[(int)(data->posY)][(int)(data->posX - data->planeX
				* 0.1)];
		new_posy = data->map[(int)(data->posY + data->planeY
				* 0.1)][(int)(data->posX)];
		if (new_posx == '0' || is_carac_map(new_posx))
			data->posX -= 0.1 * data->planeX;
		if (new_posy == '0' || is_carac_map(new_posy))
			data->posY += 0.1 * data->planeY;
	}
	else if (keycode == 100) // D
	{
		new_posx = data->map[(int)(data->posY)][(int)(data->posX + data->planeX
				* 0.1)];
		new_posy = data->map[(int)(data->posY - data->planeY
				* 0.1)][(int)(data->posX)];
		if (new_posx == '0' || is_carac_map(new_posx))
			data->posX += 0.1 * data->planeX;
		if (new_posy == '0' || is_carac_map(new_posy))
			data->posY -= 0.1 * data->planeY;
	}
	if (keycode == 65361) // fleche gauche
	{
		rad = (ALPHA * PI) / 180;
		data->dirX = data->dirX * cos(rad) - data->dirY * sin(rad);
		data->dirY = dx * sin(rad) + data->dirY * cos(rad);
		data->planeX = data->planeX * cos(rad) - data->planeY * sin(rad);
		data->planeY = px * sin(rad) + data->planeY * cos(rad);
	}
	else if (keycode == 65363) // fleche droite
	{
		rad = (-ALPHA * PI) / 180;
		data->dirX = data->dirX * cos(rad) - data->dirY * sin(rad);
		data->dirY = dx * sin(rad) + data->dirY * cos(rad);
		data->planeX = data->planeX * cos(rad) - data->planeY * sin(rad);
		data->planeY = px * sin(rad) + data->planeY * cos(rad);
	}
	if (keycode == 109)
		data->dis_map = (data->dis_map + 1) % 2;
	if (good_keycode(keycode) == 1)
	{
		mlx_clear_window(data->mlx_ptr, data->win_ptr);
		display(data);
	}
	return (1);
}
