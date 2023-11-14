#include "cub3d.h"

void	w_key(t_map *data)
{
	char		new_posx;
	char		new_posy;

	new_posx = data->map[(int)(data->posY)][(int)(data->posX + data->dirX * data->speed)];
	// char new_posx2 = data->map[(int)(data->posY)][(int)(data->posX + data->dirX * data->speed * 2)];

	new_posy = data->map[(int)(data->posY - data->dirY * data->speed)][(int)(data->posX)];
	// char new_posy2 = data->map[(int)(data->posY - data->dirY * data->speed * 2)][(int)(data->posX)];

	// printf("nb_col = %d, data->nb_line = %d\n", data->nb_col, data->nb_line);
	// printf("calcx = %f, calcy = %f\n", data->posX + data->dirX * data->speed, data->posY - data->dirY * data->speed);
	// printf("calcx2 = %f, calcy2 = %f\n", data->posX + data->dirX * data->speed * 2, data->posY - data->dirY * data->speed * 2);
	// printf("new_posx2 = %c, new_posy2 = %c\n", new_posx2, new_posy2);
	// if (data->posX + data->dirX * data->speed < data->nb_col - 1
	// 	&& data->posX + data->dirX * data->speed > 1 + data->speed
	// 	&& 
	if (new_posx != '1')
		data->posX += data->speed * data->dirX;
	// if (data->posY - data->dirY * data->speed < data->nb_line - 1 - data->speed
	// 	&& data->posY - data->dirY * data->speed > 1 + data->speed
	if (new_posy != '1')
		data->posY -= data->speed * data->dirY;
}

void	s_key(t_map *data)
{
	int		new_posx;
	int		new_posy;

	new_posx = data->map[(int)(data->posY)][(int)(data->posX - data->dirX
			* data->speed)];
	new_posy = data->map[(int)(data->posY + data->dirY
			* data->speed)][(int)(data->posX)];
	if (new_posx == '0' || is_carac_map(new_posx))
		data->posX -= data->speed * data->dirX;
	if (new_posy == '0' || is_carac_map(new_posy))
		data->posY += data->speed * data->dirY;
}

void	a_key(t_map *data)
{
	int		new_posx;
	int		new_posy;

	new_posx = data->map[(int)(data->posY)][(int)(data->posX - data->planeX
			* data->speed)];
	new_posy = data->map[(int)(data->posY + data->planeY
			* data->speed)][(int)(data->posX)];
	if (new_posx == '0' || is_carac_map(new_posx))
		data->posX -= data->speed * data->planeX;
	if (new_posy == '0' || is_carac_map(new_posy))
		data->posY += data->speed * data->planeY;
}

void	d_key(t_map *data)
{
	int		new_posx;
	int		new_posy;

	new_posx = data->map[(int)(data->posY)][(int)(data->posX + data->planeX
			* data->speed)];
	new_posy = data->map[(int)(data->posY - data->planeY
			* data->speed)][(int)(data->posX)];
	if (new_posx == '0' || is_carac_map(new_posx))
		data->posX += data->speed * data->planeX;
	if (new_posy == '0' || is_carac_map(new_posy))
		data->posY -= data->speed * data->planeY;
}
