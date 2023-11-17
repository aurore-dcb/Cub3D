#include "cub3d_bonus.h"

#define uDiv 1
#define vDiv 1
#define vMove 64

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

// fonction pour trier les sprites
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

void	sprite_casting(t_map *data)
{
	int i;
	t_coll *s;

	s = &data->sprite;
	i = -1;
	while (++i < nb_sprite(data))
	{
		s->sprite_order[i] = i;
		s->sprite_dist[i] = ((data->posX - s->sprite[i].x) * (data->posX
					- s->sprite[i].x) + (data->posY - s->sprite[i].y)
				* (data->posY - s->sprite[i].y));
	}
	sort_sprites(s->sprite_order, s->sprite_dist, nb_sprite(data));
	i = -1;
	while (++i < nb_sprite(data))
	{
		s->spritex = (s->sprite[s->sprite_order[i]].x - data->posX);
		s->spritey = s->sprite[s->sprite_order[i]].y - data->posY;
		s->invDet = 1.0 / (data->planeX * data->dirY - data->dirX
				* data->planeY);
		// if (i == 2)
		// {
		// 	printf("s->spritex : %f   - s->spritey : %f\n", s->spritex, s->spritey);
		// 	printf("s->invDet : %f\n", s->invDet);
		// }
		s->transformx = s->invDet * (data->dirY * s->spritex
				+ data->dirX * s->spritey);
		s->transformy = s->invDet * (-data->planeY * s->spritex
				- data->planeX * s->spritey);
		// s->transformy = s->invDet * (-data->planeX * s->spritey
		// 		- (data->planeY * s->spritex));
		// if (i == 1)
		// {
		// 	printf("i -> %d :\n", i);
			// printf("	data->planeY : %f\n", data->planeY);
			// printf("	data->planeX : %f\n", data->planeX);
		// 	printf("	s->transformx : %f   -   s->transformy : %f\n\n", s->transformx, s->transformy);
		// }
		s->sprite_screenx = (int)((data->width / 2) * (1 + s->transformx
					/ s->transformy));
		int vMoveScreen = (int)(vMove / s->transformy);
		if (i == 2)
		{
			printf("i -> %d :\n", i);
			printf("	data->planeY : %f\n", data->planeY);
			printf("	data->planeX : %f\n", data->planeX);
			printf("	s->transformx : %f   -   s->transformy : %f\n", s->transformx, s->transformy);
			printf("	sprite_screenx : %d\n\n", s->sprite_screenx);
		}
		// if (i == 2)
		// 	printf("move screem : %d\n", vMoveScreen);
		s->spriteHeight = abs((int)(data->height / s->transformy)) / vDiv;
		s->drawStartY = -s->spriteHeight / 2 + data->height / 2 + vMoveScreen;
		if (s->drawStartY < 0)
			s->drawStartY = 0;
		// s->drawEndY = s->spriteHeight / 2 + data->height / 2 + vMoveScreen;
		s->drawEndY = s->spriteHeight / 2 + data->height / 2 + vMoveScreen;
		if (s->drawEndY >= data->height)
			s->drawEndY = data->height - 1;
		// calculer la largeur du sprite
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
					s->color = data->tex[5][data->tex_width * s->texY + s->texX];
					if ((s->color & 0x00FFFFFF) != 0)
						data->buffer[y][stripe] = s->color;
					y++;
				}
			}
			stripe++;
		}
	}
}
