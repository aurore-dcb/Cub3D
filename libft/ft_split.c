/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 11:35:50 by aducobu           #+#    #+#             */
/*   Updated: 2023/05/26 22:25:45 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nb_mots(const char *str, char c)
{
	int	mots;
	int	sep;

	mots = 0;
	sep = 1;
	while (*str)
	{
		if (*str == c)
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

static int	nb_lettre(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
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

char	**ft_split(const char *str, char c)
{
	char	**tab;
	int		i;
	int		j;

	if (str == NULL)
		return (NULL);
	tab = malloc(sizeof(char *) * (nb_mots(str, c) + 1));
	if (tab == NULL)
		return (NULL);
	i = 0;
	while (nb_mots(str, c))
	{
		while (*str && *str == c)
			str++;
		tab[i] = malloc(sizeof(char) * nb_lettre(str, c) + 1);
		if (!tab[i])
			return (error(tab, i));
		j = 0;
		while (*str && *str != c)
			tab[i][j++] = *str++;
		tab[i++][j] = '\0';
	}
	tab[i] = 0;
	return (tab);
}
