/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:19:03 by auplisas          #+#    #+#             */
/*   Updated: 2024/10/10 22:09:06 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, char *src, size_t n)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = 0;
	while (src[size] != '\0')
		size++;
	if (n == 0)
	{
		while (src[i])
			i++;
		return (i);
	}
	while (src[i] != '\0' && i < n - 1)
	{
		{
			dst[i] = src[i];
			i++;
		}
	}
	if (i < n)
		dst[i] = '\0';
	return (size);
}
