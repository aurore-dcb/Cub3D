#include "cub3d_bonus.h"

#define uDiv 2
#define vDiv 2
#define vMove 500

int nb_sprite(t_map *data)
{
	int x;
	int y;
	int nb;

	y = 0;
	nb = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == 'C')
				nb++;
			x++;
		}
		y++;
	}
	return (nb);
}

void	sort_order(t_pair *orders, int nb)
{
	int		i;
	int		j;
	t_pair	tmp;

	i = -1;
	j = -1;
	while (++i < nb)
	{
		while (++j < nb - 1)
		{
			if (orders[j].first > orders[j + 1].first)
			{
				tmp.first = orders[j].first;
				tmp.second = orders[j].second;
				orders[j].first = orders[j + 1].first;
				orders[j].second = orders[j + 1].second;
				orders[j + 1].first = tmp.first;
				orders[j + 1].second = tmp.second;
			}
		}
	}
}

void	sort_sprites(int *order, double *dist, int nb)
{
	int		i;
	t_pair	*sprites;

	i = -1;
	sprites = malloc(sizeof(t_pair) * nb);
	if (!sprites)
		return ;
	while (++i < nb)
	{
		sprites[i].first = dist[i];
		sprites[i].second = order[i];
	}
	sort_order(sprites, nb);
	i = -1;
	while (++i < nb)
	{
		dist[i] = sprites[nb - i - 1].first;
		order[i] = sprites[nb - i - 1].second;
	}
	free(sprites);
}

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

int	change_bright(int originalColor, int reductionValue)
{
    int alpha;
    int red;
    int green;
    int blue;
	int darkerColor;

	alpha = (originalColor >> 24) & 0xFF;
    red = (originalColor >> 16) & 0xFF;
    green = (originalColor >> 8) & 0xFF;
    blue = originalColor & 0xFF;
    red -= reductionValue;
    green -= reductionValue;
    blue -= reductionValue;
	if (red < 0)
		red = 0;
	if (green < 0)
		green = 0;
	if (blue < 0)
		blue = 0;
    darkerColor = (alpha << 24) | (red << 16) | (green << 8) | blue;
    return (darkerColor);
}

void	sprite_casting(t_map *data)
{
	int i;
	t_coll *s;

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
		clock_t current_time;
		double elapsed_time;
		current_time = clock();
		elapsed_time = (double)(current_time - data->start_time) / CLOCKS_PER_SEC;
		if (i % 2 == 0)
			elapsed_time -= 0.1;
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
		int vMoveScreen = (int)(vMove / s->transformy);
		s->spriteHeight = abs((int)(data->height / s->transformy)) / vDiv;
		s->drawStartY = -s->spriteHeight / 2 + data->height / 2 + vMoveScreen;
		if (s->drawStartY < 0)
			s->drawStartY = 0;
		s->drawEndY = s->spriteHeight / 2 + data->height / 2 + vMoveScreen;
		if (s->drawEndY >= data->height)
			s->drawEndY = data->height - 1;
		s->spriteWidth = abs((int)(data->height / s->transformy)) / uDiv;
		s->drawStartX = -s->spriteWidth / 2 + s->sprite_screenx;
		if (s->drawStartX < 0)
			s->drawStartX = 0;
		s->drawEndX = s->spriteWidth / 2 + s->sprite_screenx;
		if (s->drawEndX > data->width)
			s->drawEndX = data->width;
		int stripe = s->drawStartX;
		while (stripe < s->drawEndX)
		{
			s->texX = (int)(256 * (stripe - (-s->spriteWidth / 2 + s->sprite_screenx)) * data->tex_width / s->spriteWidth) / 256;
			if (s->transformy > 0 && s->transformy < s->Zbuffer[stripe] && stripe > 0 && stripe < data->width)
			{
				int y = s->drawStartY;
				while (y < s->drawEndY)
				{
					s->d = (y - vMoveScreen) * 256 - data->height * 128 + s->spriteHeight * 128;
					s->texY = ((s->d * data->tex_height) / s->spriteHeight) / 256;
					if (data->nb_doors)
						s->color = data->tex[5][data->tex_width * s->texY + s->texX];
					else
						s->color = data->tex[4][data->tex_width * s->texY + s->texX];
					if (fmod(elapsed_time, 0.3) >= 0.1)
						s->color = change_bright(s->color, 20);
					if ((s->color & 0x00FFFFFF) != 0)
						data->buffer[y][stripe] = s->color;
					y++;
				}
			}
			stripe++;
		}
	}
}
