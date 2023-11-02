/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:05:44 by aducobu           #+#    #+#             */
/*   Updated: 2023/05/26 23:28:30 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../include/ft_printf.h"
#include "../libft.h"

int	is_an_option(char c)
{
	if (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i' || c == 'u'
		|| c == 'x' || c == 'X' || c == '%')
		return (1);
	return (0);
}

int	conversion(va_list args, char c)
{
	int	len;

	len = 0;
	if (c == 'c')
		len = ft_putchar(va_arg(args, int));
	else if (c == 's')
		len = ft_putstr_len(va_arg(args, char *));
	else if (c == 'p')
		len = ft_print_ptr(va_arg(args, unsigned long long));
	else if (c == 'd' || c == 'i')
		len = ft_print_nbr(va_arg(args, int));
	else if (c == 'u')
		len = ft_print_unsigned(va_arg(args, unsigned int));
	else if (c == 'x' || c == 'X')
		len = convert_hexa(va_arg(args, unsigned int), c);
	else if (c == '%')
		len = ft_putchar('%');
	return (len);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		nb_chars;
	va_list	args;

	i = 0;
	nb_chars = 0;
	va_start(args, format);
	if (!format)
		return (0);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			while (format[i] && format[i] == ' ')
				i++;
			if (is_an_option(format[i]))
				nb_chars += conversion(args, format[i]);
			i++;
		}
		else
			nb_chars += ft_putchar(format[i++]);
	}
	va_end(args);
	return (nb_chars);
}
