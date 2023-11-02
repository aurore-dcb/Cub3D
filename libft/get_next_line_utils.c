/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:15:28 by aducobu           #+#    #+#             */
/*   Updated: 2023/05/26 22:32:50 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	modif_stash(char *stash)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!stash)
		return ;
	while (stash[i] && stash[i] != '\n')
	{
		stash[i] = '\0';
		i++;
	}
	if (stash[i] == '\n')
	{
		stash[i++] = '\0';
		while (stash[i])
		{
			stash[j] = stash[i];
			j++;
			i++;
		}
		stash[j] = '\0';
	}
}

char	*clean_stash(char *stash)
{
	int		i;
	int		j;
	char	*new_stash;

	i = 0;
	if (!stash)
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] && stash[i] == '\n')
		i++;
	new_stash = (char *)malloc(sizeof(char) * (ft_strlen(stash) - i + 1));
	if (!new_stash)
		return (free(stash), NULL);
	j = 0;
	while (stash[i])
		new_stash[j++] = stash[i++];
	new_stash[j] = '\0';
	free(stash);
	return (new_stash);
}

int	is_new_line(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (-1);
	while (line[i])
	{
		if (line[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*just_the_line(char *str)
{
	int		i;
	char	*res;

	i = 0;
	if (!str || str[0] == '\0')
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (is_new_line(str) >= 0)
		res = malloc(sizeof(char) * (i + 2));
	else
		res = malloc(sizeof(char) * (i + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		res[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		res[i++] = '\n';
	res[i] = '\0';
	return (res);
}
