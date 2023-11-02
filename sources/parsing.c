#include "cub3d.h"

int	begin_map(char *lign)
{
	int	i;

	i = 0;
	if (!lign)
		return (0);
	while (is_spaces(lign[i]))
		i++;
	if (lign[i] == '\0')
		return (1);
	if (lign[i] != '1')
		return (0);
	else
		return (2);
	return (1);
}

int	get_map_size(t_map *data, char *lign)
{
	int	i;

	i = 0;
	if (!lign)
		return (0);
	while (lign[i])
		i++;
	if (data->nb_col < i)
		data->nb_col = i;
	return (1);
}

// while (lign[i])
// {
// 	if (is_carac_map(lign[i]))
// 		data->nb_player += 1;
// 	if (data->nb_player > 1)
// 		return (0);
// 	if (!test_valid_carac(lign[i]))
// 		return (0);
// 	i++;
// }

char	*get_first_row(int fd)
{
	char	*lign;

	lign = get_next_line(fd, 0);
	if (!lign)
		return (0);
	while (lign)
	{
		if (!begin_map(lign))
			return (0);
		else if (begin_map(lign) == 2)
			break ;
		free(lign);
		lign = get_next_line(fd, 0);
	}
	return (lign);
}

int	read_file(t_map *data, char *file)
{
	int		fd;
	char	*lign;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (printf("Error\nCan't open file\n"), 0);
	lign = get_first_row(fd);
	if (!lign)
		return (0);
	while (lign)
	{
		if (!get_map_size(data, lign))
			return (printf("Error\n"), 0);
		free(lign);
		data->nb_line += 1;
		lign = get_next_line(fd, 0);
	}
	close(fd);
	free(lign);
	return (1);
}

int	fill_map(t_map *data, char *lign, int fd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < data->nb_line)
	{
		data->map[i] = (char *)malloc((data->nb_col + 1) * sizeof(char));
		if (!data->map[i])
			return (free_char_spe(data->map, i), 0);
		j = 0;
		while (lign[j])
		{
			data->map[i][j] = lign[j];
			j++;
		}
		data->map[i][j] = '\0';
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
	lign = get_first_row(fd);
	if (!lign)
		return (0);
	if (!fill_map(data, lign, fd))
		return (0);
	close(fd);
	return (1);
}
