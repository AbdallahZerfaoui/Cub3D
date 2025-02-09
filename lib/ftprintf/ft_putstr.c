/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:30:41 by auplisas          #+#    #+#             */
/*   Updated: 2024/11/16 03:22:23 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_strlen(const char *c)
{
	size_t	i;

	i = 0;
	while (c[i] != '\0')
		i++;
	return (i);
}

void	ft_printf_putstr_fd(char *s, int fd, int *count)
{
	int	i;
	int	str_len;

	if (!s)
		ft_printf_putstr_fd("(null)", 1, count);
	else
	{
		str_len = ft_strlen(s);
		i = 0;
		while (i < str_len)
		{
			ft_printf_putchar_fd(s[i], fd, count);
			i++;
		}
	}
}
