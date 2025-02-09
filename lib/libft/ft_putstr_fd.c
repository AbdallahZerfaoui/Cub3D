/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 21:42:23 by auplisas          #+#    #+#             */
/*   Updated: 2024/10/11 22:33:51 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putstr_fd(char *s, int fd)
{
	int	i;
	int	str_len;

	str_len = ft_strlen(s);
	i = 0;
	while (i < str_len)
	{
		write(fd, &s[i], 1);
		i++;
	}
}
