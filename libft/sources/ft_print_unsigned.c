/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:05:36 by aducobu           #+#    #+#             */
/*   Updated: 2023/05/26 23:28:26 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../include/ft_printf.h"
#include "../libft.h"

int	ft_num_len(unsigned int num)
{
	int	len;

	len = 0;
	while (num != 0)
	{
		len++;
		num = num / 10;
	}
	return (len);
}

char	*ft_unsigned_itoa(unsigned int nb)
{
	int		i;
	char	*res;

	i = ft_num_len(nb);
	res = (char *)malloc(sizeof(char) * (i + 1));
	if (!res)
		return (0);
	res[i] = '\0';
	i--;
	while (nb != 0)
	{
		res[i] = nb % 10 + '0';
		nb /= 10;
		i--;
	}
	return (res);
}

int	ft_print_unsigned(unsigned int nb)
{
	int		len;
	char	*num;

	len = 0;
	if (nb == 0)
	{
		write(1, "0", 1);
		return (1);
	}
	num = ft_unsigned_itoa(nb);
	if (!num)
		return (0);
	len = ft_putstr_len(num);
	free(num);
	return (len);
}
