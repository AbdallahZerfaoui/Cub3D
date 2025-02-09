/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:10:07 by auplisas          #+#    #+#             */
/*   Updated: 2024/11/16 03:22:52 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printf_putchar_fd(char c, int fd, int *count)
{
	int	written;

	if (*count == -1)
		return ;
	written = write(fd, &c, 1);
	if (written == -1)
	{
		*count = -1;
		return ;
	}
	else
		*count += written;
}
