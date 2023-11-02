/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:05:28 by aducobu           #+#    #+#             */
/*   Updated: 2023/05/26 23:27:56 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../include/ft_printf.h"
#include "../libft.h"

int	ft_print_ptr(unsigned long p)
{
	char	*base;
	char	res[20];
	int		i;
	int		len;

	base = "0123456789abcdef";
	i = 0;
	len = 0;
	if (p == 0)
		return (ft_putstr_len("(nil)"));
	write(1, "0x", 2);
	len += 2;
	while (p)
	{
		res[i++] = base[p % 16];
		p /= 16;
	}
	while (i--)
		len += ft_putchar(res[i]);
	return (len);
}
