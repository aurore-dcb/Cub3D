/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_config_utils_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 13:21:57 by aducobu           #+#    #+#             */
/*   Updated: 2023/11/21 13:55:44 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
		return (printf("Error\nColor\n"), free_tab(color), 0);
	if (ft_atoi(color[0]) < 0 || ft_atoi(color[0]) > 255
		|| ft_atoi(color[1]) < 0 || ft_atoi(color[1]) > 255
		|| ft_atoi(color[2]) < 0 || ft_atoi(color[2]) > 255)
		return (free_tab(color), 0);
	free_tab(color);
	return (1);
}

int	check_color(t_map *data, char **tab)
{
	if (ft_strcmp(tab[0], "F") == 0 && !data->f_color)
	{
		if (!color_format(tab[1]))
			return (printf("Error\nColor\n"), 0);
		data->f_color = ft_strcpy(data->f_color, tab[1]);
		return (1);
	}
	else if (ft_strcmp(tab[0], "C") == 0 && !data->c_color)
	{
		if (!color_format(tab[1]))
			return (printf("Error\nColor\n"), 0);
		data->c_color = ft_strcpy(data->c_color, tab[1]);
		return (1);
	}
	printf("Error\nColor\n");
	return (0);
}

int	check_texture_paths(t_map *data, char **tab)
{
	int	fd;

	fd = open(tab[1], O_RDONLY);
	if (fd == -1)
		return (printf("Error\nTexture\n"), 0);
	if (strcmp(tab[0], "NO") == 0 && !data->path_n)
		data->path_n = ft_strcpy(data->path_n, tab[1]);
	else if (strcmp(tab[0], "SO") == 0 && !data->path_s)
		data->path_s = ft_strcpy(data->path_s, tab[1]);
	else if (strcmp(tab[0], "EA") == 0 && !data->path_e)
		data->path_e = ft_strcpy(data->path_e, tab[1]);
	else if (strcmp(tab[0], "WE") == 0 && !data->path_w)
		data->path_w = ft_strcpy(data->path_w, tab[1]);
	else if (strcmp(tab[0], "DO") == 0 && !data->path_d)
		data->path_d = ft_strcpy(data->path_d, tab[1]);
	else if (strcmp(tab[0], "CO") == 0 && !data->path_co)
		data->path_co = ft_strcpy(data->path_co, tab[1]);
	else
		return (close(fd), printf("Error\nTexture\n"), 0);
	data->nb_tex += 1;
	return (close(fd), 1);
}

int	if_check_texture(t_map *data, int i, char **tab)
{
	if (i != 2)
		printf("Error\n");
	else if (ft_strcmp(tab[0], "F") == 0 || ft_strcmp(tab[0], "C") == 0)
	{
		if (check_color(data, tab))
			return (free_tab(tab), 1);
	}
	else if (strcmp(tab[0], "NO") == 0 || strcmp(tab[0], "SO") == 0
		|| strcmp(tab[0], "EA") == 0 || strcmp(tab[0], "WE") == 0
		|| strcmp(tab[0], "DO") == 0 || strcmp(tab[0], "CO") == 0)
	{
		if (check_texture_paths(data, tab))
			return (free_tab(tab), 1);
	}
	else
		printf("Error\n");
	return (0);
}

int	check_texture(char *line, t_map *data)
{
	int		i;
	char	**tab;

	if (!line)
		return (0);
	tab = ft_split(line);
	i = 0;
	while (tab && tab[i])
		i++;
	if (if_check_texture(data, i, tab))
		return (1);
	return (printf("Config line : %s", line), free_tab(tab), 0);
}
