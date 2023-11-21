/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_casting_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:12:46 by aducobu           #+#    #+#             */
/*   Updated: 2023/11/21 13:52:28 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	take_coin(t_map *data)
{
	int		i;
	t_coll	*s;

	i = 0;
	s = &data->sprite;
	while (i < data->nb_sprites)
	{
		if (data->posx >= s->sprite[i].x - 0.5 && data->posx <= s->sprite[i].x
			+ 0.5 && data->posy >= s->sprite[i].y - 0.5
			&& data->posy <= s->sprite[i].y + 0.5)
		{
			data->map[(int)fabs(data->posy)][(int)fabs(data->posx)] = '0';
		}
		i++;
	}
}

void	change_bright(int color, int red_value, t_map *data, int y)
{
	int	alpha;
	int	red;
	int	green;
	int	blue;
	int	darker_color;

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
	darker_color = (alpha << 24) | (red << 16) | (green << 8) | blue;
	if (fmod(data->sprite.elapsed_time, 0.3) >= 0.1)
		data->sprite.color = darker_color;
	if ((data->sprite.color & 0x00FFFFFF) != 0)
		data->buffer[y][data->sprite.stripe] = data->sprite.color;
}

void	color_texture(t_map *d, t_coll *s)
{
	int	y;

	s->stripe = s->draw_startx - 1;
	while (++s->stripe < s->draw_endx)
	{
		s->tex_x = (int)(256 * (s->stripe - (-s->sprite_width / 2
						+ s->sprite_screenx)) * d->tex_width / s->sprite_width)
			/ 256;
		if (s->transformy > 0 && s->transformy < s->z_buffer[s->stripe]
			&& s->stripe > 0 && s->stripe < d->width)
		{
			y = s->draw_starty - 1;
			while (++y < s->draw_endy)
			{
				s->d = (y - s->vmove_screen) * 256 - d->height * 128
					+ s->sprite_height * 128;
				s->tex_y = ((s->d * d->tex_height) / s->sprite_height) / 256;
				s->color = d->tex[4][d->tex_width * s->tex_y + s->tex_x];
				if (d->nb_doors)
					s->color = d->tex[5][d->tex_width * s->tex_y + s->tex_x];
				change_bright(s->color, 20, d, y);
			}
		}
	}
}

void	texture_height(t_map *data, t_coll *s, int i)
{
	s->spritex = s->sprite[s->sprite_order[i]].x - data->posx;
	s->spritey = s->sprite[s->sprite_order[i]].y - data->posy;
	s->inv_det = 1.0 / (data->planex * data->diry - data->dirx * data->planey);
	s->transformx = s->inv_det * (data->diry * s->spritex + data->dirx
			* s->spritey);
	s->transformy = s->inv_det * (-data->planey * s->spritex - data->planex
			* s->spritey);
	s->sprite_screenx = (int)((data->width / 2) * (1 + s->transformx
				/ s->transformy));
	s->vmove_screen = (int)(VMOVE / s->transformy);
	s->sprite_height = abs((int)(data->height / s->transformy)) / VDIV;
	s->draw_starty = -s->sprite_height / 2 + data->height / 2 + s->vmove_screen;
	if (s->draw_starty < 0)
		s->draw_starty = 0;
	s->draw_endy = s->sprite_height / 2 + data->height / 2 + s->vmove_screen;
	if (s->draw_endy >= data->height)
		s->draw_endy = data->height - 1;
	s->sprite_width = abs((int)(data->height / s->transformy)) / UDIV;
	s->draw_startx = -s->sprite_width / 2 + s->sprite_screenx;
	if (s->draw_startx < 0)
		s->draw_startx = 0;
	s->draw_endx = s->sprite_width / 2 + s->sprite_screenx;
	if (s->draw_endx > data->width)
		s->draw_endx = data->width;
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
		s->sprite_dist[i] = ((data->posx - s->sprite[i].x) * (data->posx
					- s->sprite[i].x) + (data->posy - s->sprite[i].y)
				* (data->posy - s->sprite[i].y));
	}
	sort_sprites(s->sprite_order, s->sprite_dist, data->nb_sprites);
	i = -1;
	while (++i < data->nb_sprites)
	{
		s->current_time = clock();
		s->elapsed_time = (double)(s->current_time - data->start_time)
			/ CLOCKS_PER_SEC;
		if (i % 2 == 0)
			s->elapsed_time -= 0.1;
		texture_height(data, s, i);
		color_texture(data, s);
	}
}
