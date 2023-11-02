/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prints.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:05:54 by aducobu           #+#    #+#             */
/*   Updated: 2023/05/26 23:34:12 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../include/ft_printf.h"
#include "../libft.h"

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

// int	ft_strlen(char *str)
// {
// 	int	i;

// 	if (!str)
// 		return (0);
// 	i = 0;
// 	while (str[i] != '\0')
// 		i++;
// 	return (i);
// }

int	ft_putstr_len(char *str)
{
	int	i;

	i = 0;
	if (!str)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (str[i])
	{
		write(1, &(str[i]), 1);
		i++;
	}
	return (i);
}
