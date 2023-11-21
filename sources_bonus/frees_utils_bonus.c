/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 13:23:10 by aducobu           #+#    #+#             */
/*   Updated: 2023/11/21 13:23:11 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_tab_int(int **buf, t_map *data, int n)
{
	int	i;

	i = 0;
	if (!buf)
		return ;
	(void)data;
	while (i < n)
	{
		free(buf[i]);
		i++;
	}
	free(buf);
	buf = NULL;
}

void	free_buffer(unsigned int **buf, t_map *data)
{
	int	i;

	i = 0;
	if (!buf)
		return ;
	while (i < data->height && buf && buf[i] != NULL)
	{
		free(buf[i]);
		i++;
	}
	free(buf);
}

void	free_char_spe(char **tableau, int len)
{
	int	i;

	i = 0;
	if (tableau == NULL)
		return ;
	while (i < len)
	{
		free(tableau[i]);
		i++;
	}
	free(tableau);
}
