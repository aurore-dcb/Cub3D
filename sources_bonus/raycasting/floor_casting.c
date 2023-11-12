#include "cub3d.h"

unsigned int	get_color(char *s)
{
	char			**comp;
	unsigned int	color;

	comp = ft_split_char(s, ',');
    if (!comp)
        return (0);
    int r = ft_atoi(comp[0]);
    int g = ft_atoi(comp[1]);
    int b = ft_atoi(comp[2]);
	color = ((unsigned int)r << 16 | (unsigned int)g << 8 | (unsigned int)b);
	free_tab(comp);
    return (color);
}

void	floor_casting(t_map *data)
{
    int y;
    int x;
    unsigned int ceiling_color;
    unsigned int floor_color;

    ceiling_color = get_color(data->C_color);
    floor_color = get_color(data->F_color);
    x = 0;
    while (x < data->width)
    {
        y = 0;
        while (y < data->height && data->buffer[y][x] == 0)
            data->buffer[y++][x] = ceiling_color;
        while (y < data->height && data->buffer[y][x] != 0)
            y++;
        while (y < data->height && data->buffer[y][x] == 0)
            data->buffer[y++][x] = floor_color;
        x++;
    }
}
