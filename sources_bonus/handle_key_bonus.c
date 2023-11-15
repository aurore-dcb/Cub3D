#include "cub3d_bonus.h"

void	w_key(t_map *data)
{
	char		new_posx;
	char		new_posy;

	new_posx = data->map[(int)(data->posY)][(int)(data->posX + data->dirX
			* (data->speed + 0.0001))];
	new_posy = data->map[(int)(data->posY - data->dirY
			* (data->speed + 0.0001))][(int)(data->posX)];
	if (new_posx != '1')
		data->posX += data->speed * data->dirX;
	if (new_posy != '1')
		data->posY -= data->speed * data->dirY;
}

void	s_key(t_map *data)
{
	char		new_posx;
	char		new_posy;

	new_posx = data->map[(int)(data->posY)][(int)(data->posX - data->dirX
			* (data->speed + 0.0001))];
	new_posy = data->map[(int)(data->posY + data->dirY
			* (data->speed + 0.0001))][(int)(data->posX)];
	if (new_posx == '0' || is_carac_map(new_posx))
		data->posX -= data->speed * data->dirX;
	if (new_posy == '0' || is_carac_map(new_posy))
		data->posY += data->speed * data->dirY;
}

void	a_key(t_map *data)
{
	char		new_posx;
	char		new_posy;

	new_posx = data->map[(int)(data->posY)][(int)(data->posX - data->planeX
			* (data->speed + 0.0001))];
	new_posy = data->map[(int)(data->posY + data->planeY
			* (data->speed + 0.0001))][(int)(data->posX)];
	if (new_posx == '0' || is_carac_map(new_posx))
		data->posX -= data->speed * data->planeX;
	if (new_posy == '0' || is_carac_map(new_posy))
		data->posY += data->speed * data->planeY;
}

void	d_key(t_map *data)
{
	char		new_posx;
	char		new_posy;

	new_posx = data->map[(int)(data->posY)][(int)(data->posX + data->planeX
			* (data->speed + 0.0001))];
	new_posy = data->map[(int)(data->posY - data->planeY
			* (data->speed + 0.0001))][(int)(data->posX)];
	if (new_posx == '0' || is_carac_map(new_posx))
		data->posX += data->speed * data->planeX;
	if (new_posy == '0' || is_carac_map(new_posy))
		data->posY -= data->speed * data->planeY;
}
