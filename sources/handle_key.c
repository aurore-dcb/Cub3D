#include "cub3d.h"

void	w_key(t_map *data)
{
	int		new_posx;
	int		new_posy;

	new_posx = data->map[(int)(data->posY)][(int)(data->posX + data->dirX
			* SPEED)];
	new_posy = data->map[(int)(data->posY - data->dirY
			* SPEED)][(int)(data->posX)];
	if (data->posX + data->dirX * SPEED < data->nb_col - 1
		&& data->posX + data->dirX * SPEED > 1 + SPEED
		&& (new_posx == '0' || is_carac_map(new_posx)))
		data->posX += SPEED * data->dirX;
	if (data->posY - data->dirY * SPEED < data->nb_line - 1 - SPEED
		&& data->posY - data->dirY * SPEED > 1 + SPEED
		&& (new_posy == '0' || is_carac_map(new_posy)))
		data->posY -= SPEED * data->dirY;
}

void	s_key(t_map *data)
{
	int		new_posx;
	int		new_posy;

	new_posx = data->map[(int)(data->posY)][(int)(data->posX - data->dirX
			* SPEED)];
	new_posy = data->map[(int)(data->posY + data->dirY
			* SPEED)][(int)(data->posX)];
	if (new_posx == '0' || is_carac_map(new_posx))
		data->posX -= SPEED * data->dirX;
	if (new_posy == '0' || is_carac_map(new_posy))
		data->posY += SPEED * data->dirY;
}

void	a_key(t_map *data)
{
	int		new_posx;
	int		new_posy;

	new_posx = data->map[(int)(data->posY)][(int)(data->posX - data->planeX
			* SPEED)];
	new_posy = data->map[(int)(data->posY + data->planeY
			* SPEED)][(int)(data->posX)];
	if (new_posx == '0' || is_carac_map(new_posx))
		data->posX -= SPEED * data->planeX;
	if (new_posy == '0' || is_carac_map(new_posy))
		data->posY += SPEED * data->planeY;
}

void	d_key(t_map *data)
{
	int		new_posx;
	int		new_posy;

	new_posx = data->map[(int)(data->posY)][(int)(data->posX + data->planeX
			* SPEED)];
	new_posy = data->map[(int)(data->posY - data->planeY
			* SPEED)][(int)(data->posX)];
	if (new_posx == '0' || is_carac_map(new_posx))
		data->posX += SPEED * data->planeX;
	if (new_posy == '0' || is_carac_map(new_posy))
		data->posY -= SPEED * data->planeY;
}
