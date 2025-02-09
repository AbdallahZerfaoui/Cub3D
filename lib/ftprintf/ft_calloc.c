/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:25:02 by auplisas          #+#    #+#             */
/*   Updated: 2024/10/16 17:48:10 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n--)
	{
		*ptr = (unsigned char)c;
		ptr++;
	}
	return (s);
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*array;
	size_t	totalsize;

	totalsize = count * size;
	array = (char *)malloc(totalsize);
	if (array == NULL)
	{
		return (NULL);
	}
	ft_memset(array, '\0', totalsize);
	return (array);
}
