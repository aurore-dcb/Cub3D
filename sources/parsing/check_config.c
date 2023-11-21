/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmeriau <rmeriau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:00:30 by rmeriau           #+#    #+#             */
/*   Updated: 2023/11/20 14:18:01 by rmeriau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*do_check_config(t_map *data, char *line, int fd)
{
	int	i;

	i = 0;
	while (line && begin_line(line))
	{
		i = 0;
		while (line[i])
		{
			if (!((line[i] >= 9 && line[i] <= 13) || line[i] == 32)
				&& line[i++] != '\n')
			{
				if (!check_texture(line, data))
					return (free(line), get_next_line(fd, 1), close(fd), NULL);
				break ;
			}
			i++;
		}
		free(line);
		line = get_next_line(fd, 0);
	}
	if (!line)
		printf("Error\n");
	return (line);
}

int	check_config(char **argv, t_map *data)
{
	int		fd;
	char	*line;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (printf("Error\nCan't open file map\n"), 0);
	line = get_next_line(fd, 0);
	if (!line)
		return (printf("Error\n"), close(fd), 0);
	line = do_check_config(data, line, fd);
	if (!line)
		return (close(fd), 0);
	if (!data->c_color || !data->f_color)
		return (printf("Error\nMissing color\n"), get_next_line(fd, 1),
			free(line), close(fd), 0);
	else if (!data->path_e || !data->path_n || !data->path_s || !data->path_w)
	{
		get_next_line(fd, 1);
		return (printf("Error\nMissing texture\n"), free(line), close(fd), 0);
	}
	if (!read_file(data, line, fd))
		return (close(fd), 0);
	close(fd);
	return (1);
}

int	check_map(t_map *data)
{
	if (!beg_parse_map(data))
		return (printf("Error\nEmpty line\n"), 0);
	if (!test_rows(data))
		return (printf("Error\nRows wall\n"), 0);
	if (!test_cols_beg(data))
		return (printf("Error\nColumns wall\n"), 0);
	if (!test_cols_end(data))
		return (printf("Error\nColumns wall\n"), 0);
	if (!test_empty(data))
		return (printf("Error\nNeeded wall\n"), 0);
	if (!test_invalid_char(data))
		return (printf("Error\nInvalid char\n"), 0);
	if (!test_player(data))
		return (0);
	return (1);
}
