/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 11:41:12 by aducobu           #+#    #+#             */
/*   Updated: 2023/05/27 02:06:33 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, int len)
{
	int		i;
	int		j;
	char	*res;

	if (!s)
		return (NULL);
	if ((int)start > ft_strlen(s))
		return (ft_strdup(""));
	if ((size_t)len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	res = malloc(sizeof(char) * len + 1);
	if (!res)
		return (NULL);
	i = start;
	j = 0;
	while (i < ft_strlen(s) && j < len)
	{
		res[j++] = s[i++];
	}
	res[j] = '\0';
	return (res);
}
