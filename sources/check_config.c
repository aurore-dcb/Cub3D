#include "cub3d.h"

int	check_color(t_map *data, char **tab)
{
	if (ft_strcmp(tab[0], "F") == 0 && !data->F_color)
	{
		data->F_color = ft_strcpy(data->F_color, tab[1]);
		return (1);
	}
	else if (ft_strcmp(tab[0], "C") == 0 && !data->C_color)
	{
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
		printf("Error Bad path for texture\n");
	// return (0);
	if (strcmp(tab[0], "NO") == 0 && !data->path_N)
		data->path_N = ft_strcpy(data->path_N, tab[1]);
	if (strcmp(tab[0], "SO") == 0 && !data->path_S)
		data->path_S = ft_strcpy(data->path_S, tab[1]);
	if (strcmp(tab[0], "EA") == 0 && !data->path_E)
		data->path_E = ft_strcpy(data->path_E, tab[1]);
	if (strcmp(tab[0], "WE") == 0 && !data->path_W)
		data->path_W = ft_strcpy(data->path_W, tab[1]);
	return (1);
	close(fd);
}

int	check_texture(char *line, t_map *data)
{
	int		i;
	int		fd;
	char	**tab;

	if (!line)
		return (0);
	tab = ft_split(line);
	i = 0;
	while (tab[i])
		i++;
	if (i > 2) // que 2 element dans la ligne de texture
		return (free_tab(tab), printf("Error > 2\n"), 0);
	if (ft_strcmp(tab[0], "F") == 0 || ft_strcmp(tab[0], "C") == 0)
	{
		if (!check_color(data, tab))
			return (free_tab(tab), printf("Error\nColor\n"), 0);
		// check couleur sol et ciel
		// if (ft_strcmp(tab[0], "F") == 0 && !data->F_color)
		// {
		// 	data->F_color = ft_strcpy(data->F_color, tab[1]);
		// }
		// else if (ft_strcmp(tab[0], "C") == 0 && !data->C_color)
		// {
		// 	data->C_color = ft_strcpy(data->C_color, tab[1]);
		// }
	}
	else if (strcmp(tab[0], "NO") == 0 || strcmp(tab[0], "SO") == 0
			|| strcmp(tab[0], "EA") == 0 || strcmp(tab[0], "WE") == 0)
	{
		//check direction
		if (!check_texture_paths(data, tab))
			return (free_tab(tab), printf("Error\nTextures\n"), 0);
		// fd = open(tab[1], O_RDONLY);
		// if (fd == -1)
		// 	printf("Error\nBad path for texture\n");
		// if (strcmp(tab[0], "NO") == 0 && !data->path_N)
		// 	data->path_N = ft_strcpy(data->path_N, tab[1]);
		// if (strcmp(tab[0], "SO") == 0 && !data->path_S)
		// 	data->path_S = ft_strcpy(data->path_S, tab[1]);
		// if (strcmp(tab[0], "EA") == 0 && !data->path_E)
		// 	data->path_E = ft_strcpy(data->path_E, tab[1]);
		// if (strcmp(tab[0], "WE") == 0 && !data->path_W)
		// 	data->path_W = ft_strcpy(data->path_W, tab[1]);
		// close(fd);
	}
	free_tab(tab);
	return (1);
}

int	begin_line(char *line)
{
	int	i;

	i = 0;
	while ((line[i] >= 9 && line[i] <= 13) || line[i] == 32)
		i++;
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
	line = get_next_line(fd);
	if (!line)
		return (printf("Error\n"), 0);
	while (line) // et que la ligne ne commence pas par N S E W F C
	{
		// printf("\nn%d : ", index++);
		i = 0;
		while (line[i]  && begin_line(line))
		{
			if (!((line[i] >= 9 && line[i] <= 13) || line[i] == 32)
				&& line[i++] != '\n')
			{
				// il y a des caracteres autres que des espaces => check des donnees
				check_texture(line, data);
				break ;
			}
			i++;
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	free(line);
	return (1);
}
