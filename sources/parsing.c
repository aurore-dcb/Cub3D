#include "cub3d.h"
#include "libft.h"

int	ft_extantion(char *map)
{
	if (ft_strlen(map) < 5)
		return (printf("Error\nWrong format\n"), 0);
	map = &map[ft_strlen(map) - 4];
	if (ft_strcmp(map, ".map") != 0)
		return (printf("Error\nWrong format\n"), 0);
	return (1);
}


int	ft_parsing(int argc, char **argv, char **env, t_map *data)
{
	if (argc != 2)
		return (printf("Error\nWrong number of arguments\n"), 0);
	if (!ft_extantion(argv[1]))
		return (0);
    if (!check_config(argv, data))
		return (0);
	return (1);
}