/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmeriau <rmeriau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:00:48 by rmeriau           #+#    #+#             */
/*   Updated: 2023/11/20 11:00:49 by rmeriau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_sp(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	is_digit_map(char c)
{
	if (c == '1' || c == '0')
		return (1);
	return (0);
}

int	is_carac_map(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int	test_valid_carac(char c)
{
	if (!is_carac_map(c) && !is_digit_map(c) && !is_sp(c))
		return (0);
	return (1);
}
