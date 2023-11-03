/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:15:10 by aducobu           #+#    #+#             */
/*   Updated: 2023/11/03 10:59:35 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	int		j;
	int		len_1;
	int		len_2;
	char	*tmp;

	if (!s1 && !s2)
		return (NULL);
	j = 0;
	len_1 = ft_strlen(s1);
	len_2 = ft_strlen(s2);
	tmp = (char *)malloc(sizeof(char) * (len_1 + len_2 + 1));
	if (!tmp)
		return (NULL);
	ft_strcpy_gnl(tmp, s1);
	while (j < len_2)
	{
		tmp[len_1 + j] = s2[j];
		j++;
	}
	tmp[len_1 + j] = '\0';
	return (tmp);
}

char	*save_line(char *line)
{
	int		i;
	char	*tmp;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (!line[i])
		return (NULL);
	tmp = ft_strdup(line + i + 1);
	if (!tmp)
		return (NULL);
	if (!tmp[0])
		return (free(tmp), NULL);
	line[i + 1] = '\0';
	return (tmp);
}

char	*get_read(int fd, char *buf, char *res)
{
	int		size;
	char	*tmp;

	tmp = NULL;
	size = read(fd, buf, BUFFER_SIZE);
	while (size > 0)
	{
		buf[size] = 0;
		if (!res)
			res = ft_strdup(buf);
		else
		{
			tmp = res;
			res = ft_strjoin(tmp, buf);
			free(tmp);
		}
		if (!res)
			return (NULL);
		if (ft_strchr(buf, '\n'))
			return (res);
		size = read(fd, buf, BUFFER_SIZE);
	}
	return (res);
}

char	*get_next_line(int fd, int to_free)
{
	static char	*res;
	char		*line;
	char		*tmp;
	char		*buf;

	if (to_free)
		return (free(res), NULL);
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	line = get_read(fd, buf, res);
	free(buf);
	if (!line)
		return (NULL);
	res = save_line(line);
	tmp = ft_strdup(line);
	free(line);
	return (tmp);
}
