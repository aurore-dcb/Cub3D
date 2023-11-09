#include "cub3d.h"

void display_map(char **map)
{
	int i = 0;
	int j;

	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			printf("%c", map[i][j]);
			j++;
		}
		i++;
		printf("\n");
	}
}

void	init_map(t_map *data)
{
    ft_memset(data, 0, sizeof(t_map));
	data->x_player = -1;
	data->y_player = -1;
    data->width = 800;
    data->height = 600;
}

void loop(t_map *data)
{
    data->mlx_ptr = mlx_init();
    if (!data->mlx_ptr)
    {
        printf("Error\nCannot init window\n");
        return ;
    }
    data->win_ptr = mlx_new_window(data->mlx_ptr, data->width, data->height,
		"Cub3D");
    if (!data->win_ptr)
		return (ft_printf("Error\nCannot display window\n"), free(data->win_ptr));
    //charger les texture
	
	//affichage
	display(data);
	//gerer les touches
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, key_hook, data);
	mlx_hook(data->win_ptr, 17, 1L << 17, mlx_loop_end, data->mlx_ptr);
	mlx_loop(data->mlx_ptr);
}

// int main(int argc, char **argv, char **env)
// {
// 	t_map	data;

// 	init_map(&data);
// 	if (!ft_parsing(argc, argv, env, &data))
// 		return (free_data(&data), 1);
// 	if (!get_map(&data, argv[1]))
// 		return (free_data(&data), 1);
// 	if (!check_map(&data))
// 		return (free_data(&data), 1);
// 	//afficher la map
// 	display_map(data.map);
// 	//determiner les coordonnees du vecteur direction au debut
// 	coor_direction_begin(&data);
// 	// boucle d'affiche de la fenetre
// 	loop(&data);
//     free_mlx(&data);
// 	free_data(&data);
// 	return (0);
// }

void img_pix_put(t_image *img, int x, int y, int color)
{
    char *pixel;
    pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
    *(int *)pixel = color;
}

void draw_rectangle(t_image *img, int x, int y, int width, int height, int color)
{
    for (int i = y; i < y + height; i++)
    {
        for (int j = x; j < x + width; j++)
        {
            img_pix_put(img, j, i, color);
        }
    }
}

void draw_circle(t_image *img, int x, int y, int radius, int color)
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


int main()
{
    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, 800, 600, "Map Display");

    int pixel_size = 30;
    int player_radius = pixel_size / 4;

    t_image img;
    img.mlx_img = mlx_new_image(mlx, 800, 600);
    img.addr = mlx_get_data_addr(img.mlx_img, &img.bpp, &img.line_len, &img.endian);

    char *map[] = {
        "11111111111111111",
        "10000001000000001",
        "10000000000001001",
        "10001010001000001",
        "1000000000W000011",
        "10100001000000101",
        "10000000000000101",
        "11111111111111111"};

    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 17; x++)
        {
            int square_x = x * pixel_size;
            int square_y = y * pixel_size;

            if (map[y][x] == '1')
            {
                draw_rectangle(&img, square_x, square_y, pixel_size, pixel_size, 0x0000FF);
            }
            else if (map[y][x] == 'W')
            {
                draw_rectangle(&img, square_x, square_y, pixel_size, pixel_size, 0xFFFFFF);
                int center_x = square_x + (pixel_size / 2);
                int center_y = square_y + (pixel_size / 2);
                draw_circle(&img, center_x, center_y, player_radius, 0x00FF00);
            }
            else
            {
                draw_rectangle(&img, square_x, square_y, pixel_size, pixel_size, 0xFFFFFF);
            }
        }
    }

    mlx_put_image_to_window(mlx, win, img.mlx_img, 0, 0);
    mlx_loop(mlx);

    return 0;
}


