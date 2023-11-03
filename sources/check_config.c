#include "cub3d.h"

int	color_format(char *tab)
{
	int		i;
	char	**color;

	i = 0;
	color = ft_split_char(tab, ',');
	if (!color)
		return (0);
	while (color[i])
		i++;
	if (i != 3)
		return (free_tab(color), 1);
	if (ft_atoi(color[0]) < 0 || ft_atoi(color[0]) > 255
		|| ft_atoi(color[1]) < 0 || ft_atoi(color[1]) > 255
		|| ft_atoi(color[2]) < 0 || ft_atoi(color[2]) > 255)
		return (free_tab(color), 0);
	free_tab(color);
	return (1);
}

int	check_color(t_map *data, char **tab)
{
	if (ft_strcmp(tab[0], "F") == 0 && !data->F_color)
	{
		if (!color_format(tab[1]))
			return (0);
		data->F_color = ft_strcpy(data->F_color, tab[1]);
		return (1);
	}
	else if (ft_strcmp(tab[0], "C") == 0 && !data->C_color)
	{
		if (!color_format(tab[1]))
			return (0);
		data->C_color = ft_strcpy(data->C_color, tab[1]);
		return (1);
	}
	return (0);
}

int	check_texture_paths(t_map *data, char **tab)
{
	int	fd;

	fd = open(tab[1], O_RDONLY);
	if (fd == -1)
		return (0);
	if (strcmp(tab[0], "NO") == 0 && !data->path_N)
		data->path_N = ft_strcpy(data->path_N, tab[1]);
	else if (strcmp(tab[0], "SO") == 0 && !data->path_S)
		data->path_S = ft_strcpy(data->path_S, tab[1]);
	else if (strcmp(tab[0], "EA") == 0 && !data->path_E)
		data->path_E = ft_strcpy(data->path_E, tab[1]);
	else if (strcmp(tab[0], "WE") == 0 && !data->path_W)
		data->path_W = ft_strcpy(data->path_W, tab[1]);
	else
	{
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
	close(fd);
}

int	check_texture(char *line, t_map *data)
{
	int		i;
	char	**tab;

	if (!line)
		return (0);
	tab = ft_split(line);
	i = 0;
	while (tab[i])
		i++;
	if (i > 2)
		return (free_tab(tab), printf("Error\n"), 0);
	if (ft_strcmp(tab[0], "F") == 0 || ft_strcmp(tab[0], "C") == 0)
	{
		if (!check_color(data, tab))
			return (free_tab(tab), printf("Error\nColor\n"), 0);
	}
	else if (strcmp(tab[0], "NO") == 0 || strcmp(tab[0], "SO") == 0
			|| strcmp(tab[0], "EA") == 0 || strcmp(tab[0], "WE") == 0)
	{
		if (!check_texture_paths(data, tab))
			return (free_tab(tab), printf("Error\nTexture\n"), 0);
	}
	free_tab(tab);
	return (1);
}

int	begin_line(char *line)
{
	int	i;

	i = 0;
	while (((line[i] >= 9 && line[i] <= 13) && line[i] != '\n')
		|| line[i] == 32)
		i++;
	if (line[i] == '\n')
		return (1);
	if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W'
		|| line[i] == 'C' || line[i] == 'F')
		return (1);
	return (0);
}

int	check_config(char **argv, t_map *data)
{
	int		index;
	int		fd;
	int		i;
	char	*line;

	index = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (printf("Error\nCan't open file map\n"), 0);
	line = get_next_line(fd, 0);
	if (!line)
		return (printf("Error\n"), close(fd), 0);
	while (line && begin_line(line))
	{
		i = 0;
		while (line[i])
		{
			if (!((line[i] >= 9 && line[i] <= 13) || line[i] == 32)
				&& line[i++] != '\n')
			{
				if (!check_texture(line, data))
					return (free(line), get_next_line(fd, 1), close(fd), 0);
				break ;
			}
			i++;
		}
		free(line);
		line = get_next_line(fd, 0);
		index++;
	}
	close(fd);
	free(line);
	get_next_line(fd, 1);
	if (!data->C_color || !data->F_color || !data->path_E || !data->path_N
		|| !data->path_S || !data->path_W)
		return (printf("Error\nNo enough informations\n"), 0);
	return (1);
}
