
#include "cub3d.h"

void	draw_rectangle(t_image *img, int x, int y, int width, int height, int color)
{
	for (int i = y; i < y + height; i++)
	{
		for (int j = x; j < x + width; j++)
		{
			img_pix_put(img, j, i, color);
		}
	}
}

void	draw_circle(t_image *img, int x, int y, int radius, int color)
{
	for (int i = y - radius; i <= y + radius; i++)
	{
		for (int j = x - radius; j <= x + radius; j++)
		{
			if ((i - y) * (i - y) + (j - x) * (j - x) <= radius * radius)
			{
				img_pix_put(img, j, i, color);
			}
		}
	}
}

int	mini_map(t_map *data)
{
	int		map_width;
	int		map_height;
	int		pixel_size;
	int		player_radius;
	t_image	img;
	int		square_x;
	int		square_y;
	int		center_x;
	int		center_y;

	map_width = data->nb_col - 1;
	map_height = data->nb_line;
	pixel_size = 8;
	player_radius = pixel_size / 4;
	img.mlx_img = mlx_new_image(data->mlx_ptr, map_width * pixel_size,
			map_height * pixel_size);
	img.addr = mlx_get_data_addr(img.mlx_img, &img.bpp, &img.line_len,
			&img.endian);
	for (int y = 0; y < map_height; y++)
	{
		for (int x = 0; x < map_width; x++)
		{
			square_x = x * pixel_size;
			square_y = y * pixel_size;
			if (data->map[y][x] == '1')
			{
				draw_rectangle(&img, square_x, square_y, pixel_size, pixel_size,
					0x0000FF);
			}
			else if (data->map[y][x] == 'W')
			{
				draw_rectangle(&img, square_x, square_y, pixel_size, pixel_size,
					0xFFFFFF);
			}
			else
			{
				draw_rectangle(&img, square_x, square_y, pixel_size, pixel_size,
					0xFFFFFF);
			}
		}
	}
	// printf("data->posX = %f, data->posY = %f\n", data->posX, data->posY);
	center_x = data->posX * (pixel_size);
	center_y = data->posY * (pixel_size);
	draw_circle(&img, center_x, center_y, player_radius, 0xFF0000);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, img.mlx_img, 0, 0);
	return (0);
}
