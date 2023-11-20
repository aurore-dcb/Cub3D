#include "cub3d_bonus.h"

void take_coin(t_map *data)
{
	int i;
	t_coll *s;

	i = 0;
	s = &data->sprite;
	while (i < data->nb_sprites)
	{
		if (data->posX >= s->sprite[i].x - 0.5 && data->posX <= s->sprite[i].x + 0.5
			&& data->posY >= s->sprite[i].y - 0.5 && data->posY <= s->sprite[i].y + 0.5)
		{
			data->map[(int)fabs(data->posY)][(int)fabs(data->posX)] = '0';
		}
		i++;
	}
}

int	change_bright(int color, int red_value)
{
    int alpha;
    int red;
    int green;
    int blue;
	int darkerColor;

	alpha = (color >> 24) & 0xFF;
    red = (color >> 16) & 0xFF;
    green = (color >> 8) & 0xFF;
    blue = color & 0xFF;
    red -= red_value;
    green -= red_value;
    blue -= red_value;
	if (red < 0)
		red = 0;
	if (green < 0)
		green = 0;
	if (blue < 0)
		blue = 0;
    darkerColor = (alpha << 24) | (red << 16) | (green << 8) | blue;
    return (darkerColor);
}

void color_texture(t_map *data, t_coll *s)
{
	int y;

	s->stripe = s->drawStartX - 1;
	while (++s->stripe < s->drawEndX)
	{
		s->texX = (int)(256 * (s->stripe - (-s->spriteWidth / 2 + s->sprite_screenx)) * data->tex_width / s->spriteWidth) / 256;
		if (s->transformy > 0 && s->transformy < s->Zbuffer[s->stripe] && s->stripe > 0 && s->stripe < data->width)
		{
			y = s->drawStartY;
			while (y < s->drawEndY)
			{
				s->d = (y - s->vMoveScreen) * 256 - data->height * 128 + s->spriteHeight * 128;
				s->texY = ((s->d * data->tex_height) / s->spriteHeight) / 256;
				if (data->nb_doors)
					s->color = data->tex[5][data->tex_width * s->texY + s->texX];
				else
					s->color = data->tex[4][data->tex_width * s->texY + s->texX];
				if (fmod(s->elapsed_time, 0.3) >= 0.1)
					s->color = change_bright(s->color, 20);
				if ((s->color & 0x00FFFFFF) != 0)
					data->buffer[y][s->stripe] = s->color;
				y++;
			}
		}
	}
}

void texture_height(t_map *data, t_coll *s, int i)
{
	s->spritex = s->sprite[s->sprite_order[i]].x - data->posX;
	s->spritey = s->sprite[s->sprite_order[i]].y - data->posY;
	s->invDet = 1.0 / (data->planeX * data->dirY - data->dirX
			* data->planeY);
	s->transformx = s->invDet * (data->dirY * s->spritex
			+ data->dirX * s->spritey);
	s->transformy = s->invDet * (-data->planeY * s->spritex
			- data->planeX * s->spritey);
	s->sprite_screenx = (int)((data->width / 2) * (1 + s->transformx
				/ s->transformy));
	s->vMoveScreen = (int)(vMove / s->transformy);
	s->spriteHeight = abs((int)(data->height / s->transformy)) / vDiv;
	s->drawStartY = -s->spriteHeight / 2 + data->height / 2 + s->vMoveScreen;
	if (s->drawStartY < 0)
		s->drawStartY = 0;
	s->drawEndY = s->spriteHeight / 2 + data->height / 2 + s->vMoveScreen;
	if (s->drawEndY >= data->height)
		s->drawEndY = data->height - 1;
	s->spriteWidth = abs((int)(data->height / s->transformy)) / uDiv;
	s->drawStartX = -s->spriteWidth / 2 + s->sprite_screenx;
	if (s->drawStartX < 0)
		s->drawStartX = 0;
	s->drawEndX = s->spriteWidth / 2 + s->sprite_screenx;
	if (s->drawEndX > data->width)
		s->drawEndX = data->width;
}

void	sprite_casting(t_map *data)
{
	int		i;
	t_coll	*s;

	s = &data->sprite;
	i = -1;
	take_coin(data);
	while (++i < data->nb_sprites)
	{
		s->sprite_order[i] = i;
		s->sprite_dist[i] = ((data->posX - s->sprite[i].x) * (data->posX
					- s->sprite[i].x) + (data->posY - s->sprite[i].y)
				* (data->posY - s->sprite[i].y));
	}
	sort_sprites(s->sprite_order, s->sprite_dist, data->nb_sprites);
	i = -1;
	while (++i < data->nb_sprites)
	{
		s->current_time = clock();
		s->elapsed_time = (double)(s->current_time - data->start_time) / CLOCKS_PER_SEC;
		if (i % 2 == 0)
			s->elapsed_time -= 0.1;
		texture_height(data, s, i);
		color_texture(data, s);
	}
}
