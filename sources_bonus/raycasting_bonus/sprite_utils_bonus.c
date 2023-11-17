#include "cub3d_bonus.h"

void fill_sprite(t_map *data)
{
    int x;
    int y;
    int i;

    y = 0;
    i = 0;
    while (data->map[y])
    {
        x = 0;
        while (data->map[y][x])
        {
            if (data->map[y][x] == 'C')
            {
                data->sprite.sprite[i].x = (double)(x) + 0.5;
                data->sprite.sprite[i].y = (double)(y) + 0.5;
                data->sprite.sprite[i++].texture = 5;
            }
            x += 1;
        }
        y += 1;
    }
}

int init_sprite(t_map *data)
{
    data->sprite.sprite = malloc(sizeof(t_sprite) * nb_sprite(data));
    if (!data->sprite.sprite)
        return (printf("Error\nMalloc sprites\n"), 0);
    fill_sprite(data);
    data->sprite.Zbuffer = malloc(sizeof(double) * data->width);
    if (!data->sprite.Zbuffer)
        return (printf("Error\nMalloc sprites\n"), 0);
    data->sprite.sprite_order = malloc(sizeof(int) * nb_sprite(data));
    if (!data->sprite.sprite_order)
        return (printf("Error\nMalloc sprites\n"), 0);
    data->sprite.sprite_dist = malloc(sizeof(double) * nb_sprite(data));
    if (!data->sprite.sprite_dist)
        return (printf("Error\nMalloc sprites\n"), 0);
    data->nb_sprites = nb_sprite(data);
    return (1);
}
