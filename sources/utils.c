/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 11:35:50 by aducobu           #+#    #+#             */
/*   Updated: 2023/11/03 11:43:02 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	in_charset(char c, char charset)
{
	return (c == charset);
}

static int	nb_mots(const char *str, char charset)
{
	int	mots;
	int	sep;

	mots = 0;
	sep = 1;
	while (*str)
	{
		if (in_charset(*str, charset))
			sep = 1;
		else if (sep == 1)
		{
			mots++;
			sep = 0;
		}
		str++;
	}
	return (mots);
}

static int	nb_lettre(const char *s, char charset)
{
	int	i;

	i = 0;
	while (s[i] && !in_charset(s[i], charset))
		i++;
	return (i);
}

static char	**error(char **res, int i)
{
	while (i < 0)
	{
		free(res[i]);
		i--;
	}
	free(res);
	return (NULL);
}

char	**ft_split_char(const char *str, char charset)
{
	char	**tab;
	int		i;
	int		j;

	if (str == NULL)
		return (NULL);
	tab = malloc(sizeof(char *) * (nb_mots(str, charset) + 1));
	if (tab == NULL)
		return (NULL);
	i = 0;
	while (nb_mots(str, charset))
	{
		while (*str && in_charset(*str, charset))
			str++;
		tab[i] = malloc(sizeof(char) * nb_lettre(str, charset) + 1);
		if (!tab[i])
			return (error(tab, i));
		j = 0;
		while (*str && !in_charset(*str, charset))
			tab[i][j++] = *str++;
		tab[i++][j] = '\0';
	}
	tab[i] = 0;
	return (tab);
}
