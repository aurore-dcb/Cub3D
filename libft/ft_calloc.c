/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 11:21:58 by aducobu           #+#    #+#             */
/*   Updated: 2023/05/27 02:05:28 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(int count, int size)
{
	void	*str;

	if ((size_t)size > sizeof(char) * 2147483424 || (size_t)count > sizeof(char)
		* 2147483424)
		return (NULL);
	str = malloc(count * size);
	if (str == NULL)
		return (NULL);
	ft_bzero(str, (count * size));
	return (str);
}
