#include "cub3d_bonus.h"

void fill_sprite(t_map *data)
{
    double x;
    double y;
    int i;

    y = 0;
    i = 0;
    while (data->map[(int)y])
    {
        x = 0;
        while (data->map[(int)y][(int)x])
        {
            if (data->map[(int)y][(int)x] == 'C')
            {
                data->sprite.sprite[i].x = x + 0.5;
                data->sprite.sprite[i].y = y + 0.5;
                data->sprite.sprite[i++].texture = 5;
            }
            x++;
        }
        y++;
    }
}

int init_sprite(t_map *data)
{
    printf("nb sprite : %d\n", data->nb_sprites);
    data->sprite.sprite = malloc(sizeof(t_sprite) * data->nb_sprites);
    if (!data->sprite.sprite)
        return (printf("Error\nMalloc sprites\n"), 0);
    //remplir le tableau
    fill_sprite(data);
    // --- afficher les donnees des sprites ---
    int i = 0;
    while (i < data->nb_sprites)
    {
        printf("x : %f\n", data->sprite.sprite[i].x);
        printf("y : %f\n", data->sprite.sprite[i].y);
        printf("tex : %d\n", data->sprite.sprite[i].texture);
        i++;
    }
    // ----------------------------------------
    data->sprite.Zbuffer = malloc(sizeof(double) * data->width);
    if (!data->sprite.Zbuffer)
        return (printf("Error\nMalloc sprites\n"), 0);
    data->sprite.sprite_order = malloc(sizeof(int) * data->nb_sprites);
    if (!data->sprite.sprite_order)
        return (printf("Error\nMalloc sprites\n"), 0);
    data->sprite.sprite_dist = malloc(sizeof(double) * data->nb_sprites);
    if (!data->sprite.sprite_dist)
        return (printf("Error\nMalloc sprites\n"), 0);
    return (1);
}
