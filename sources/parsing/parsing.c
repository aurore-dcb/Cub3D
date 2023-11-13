#include "cub3d.h"

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

int	read_file(t_map *data, char *line, int fd)
{
	if (!line)
		return (0);
	while (line)
	{
		if (!get_map_size(data, line))
			return (printf("Error map size\n"), 0);
		free(line);
		data->nb_line += 1;
		line = get_next_line(fd, 0);
	}
	free(line);
	return (1);
}

int	ft_extantion(char *map)
{
	int i;

	i = ft_strlen(map) - 1;
	while (i > 0 && map[i] != '/')
		i--;
	if (ft_strlen(map) - i - 1 < 5)
		return (0);
	map = &map[ft_strlen(map) - 4];
	if (ft_strcmp(map, ".cub") != 0)
		return (0);
	return (1);
}

int	ft_parsing(int argc, char **argv, char **env, t_map *data)
{
	if (!env)
		return (printf("Error\nEnv\n"), 1);
	
	if (argc != 2)
		return (printf("Error\nWrong number of arguments\n"), 0);
	if (!ft_extantion(argv[1]))
		return (printf("Error\nWrong format\n"), 0);
	if (!check_config(argv, data))
		return (0);
	return (1);
}
