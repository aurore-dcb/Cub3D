/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 11:35:50 by aducobu           #+#    #+#             */
/*   Updated: 2023/11/04 10:47:25 by aducobu          ###   ########.fr       */
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
	int	i;

	mots = 0;
	sep = 1;
	i = 0;
	while (str[i])
	{
		if (in_charset(str[0], charset) || in_charset(str[ft_strlen(str) - 1],
				charset))
			return (0);
		if (in_charset(str[i], charset))
			sep = 1;
		else if (sep == 1)
		{
			mots++;
			sep = 0;
		}
		i++;
		if (in_charset(str[i], charset) && in_charset(str[i - 1], charset))
			return (0);
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
	int		i;
	int		j;
	int		words;
	char	**tab;

	if (!str)
		return (NULL);
	words = nb_mots(str, charset);
	tab = malloc(sizeof(char *) * (words + 1));
	if (tab == NULL || words == 0)
		return (NULL);
	i = 0;
	while (i < words)
	{
		if (*str && in_charset(*str, charset))
			str++;
		tab[i] = malloc(sizeof(char) * nb_lettre(str, charset) + 1);
		if (!tab[i])
			return (error(tab, i));
		j = 0;
		while (*str && !in_charset(*str, charset))
			tab[i][j++] = *str++;
		tab[i++][j] = '\0';
	}
	return (tab[i] = 0, tab);
}
