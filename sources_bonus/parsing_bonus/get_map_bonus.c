#include "cub3d_bonus.h"

int	get_map_size(t_map *data, char *lign)
{
	int	i;

	i = 0;
	if (!lign)
		return (0);
	while (lign[i])
		i++;
	i--;
	if (data->nb_col < i)
		data->nb_col = i;
	return (1);
}

void	do_fill_map(t_map *data, char *lign, int i)
{
	int	j;
	int	len;

	j = 0;
	len = ft_strlen(lign);
	while (j < len)
	{
		data->map[i][j] = lign[j];
		if (is_carac_map(data->map[i][j], data) && data->map[i][j] != 'C')
		{
			data->x_player = i;
			data->y_player = j;
			data->nb_player += 1;
		}
		j++;
		if (j == len - 1 && lign[j] && lign[j] == '\n')
			break ;
	}
	data->map[i][j] = '\0';
}

int	fill_map(t_map *data, char *lign, int fd)
{
	int	i;

	i = 0;
	while (i < data->nb_line)
	{
		data->map[i] = (char *)malloc((ft_strlen(lign) + 1) * sizeof(char));
		if (!data->map[i])
			return (free_char_spe(data->map, i), 0);
		do_fill_map(data, lign, i);
		free(lign);
		lign = get_next_line(fd, 0);
		i++;
	}
	data->map[i] = 0;
	return (1);
}

int	get_map(t_map *data, char *file)
{
	int		fd;
	char	*lign;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (printf("Error\nCan't open file\n"), 0);
	data->map = (char **)malloc((data->nb_line + 1) * sizeof(char *));
	if (!data->map)
		return (printf("Error\n"), 0);
	lign = get_next_line(fd, 0);
	if (!lign)
		return (printf("Error\n"), close(fd), 0);
	while (lign && begin_line(lign))
	{
		free(lign);
		lign = get_next_line(fd, 0);
	}
	if (!fill_map(data, lign, fd))
		return (close(fd), 0);
	close(fd);
	return (1);
}
