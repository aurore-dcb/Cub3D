/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 11:32:22 by aducobu           #+#    #+#             */
/*   Updated: 2023/05/27 02:05:19 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, int len)
{
	int				i;
	unsigned char	*d;
	unsigned char	*s;

	i = 0;
	if (dst == NULL && src == NULL)
		return (NULL);
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	if (d > s)
	{
		while (i < len)
		{
			d[len - 1] = s[len - 1];
			len--;
		}
	}
	else
	{
		i--;
		while (++i < len)
			d[i] = s[i];
	}
	return (dst);
}
