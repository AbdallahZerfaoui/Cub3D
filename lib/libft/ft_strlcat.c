/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:17:14 by auplisas          #+#    #+#             */
/*   Updated: 2024/10/10 22:08:52 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <string.h>
#include "libft.h"

size_t	ft_strlcat(char *buffer, char *src, size_t size)
{
	size_t	sizeofbuffer;
	size_t	sizeofsrc;
	size_t	j;
	size_t	i;

	sizeofbuffer = 0;
	sizeofsrc = 0;
	while (buffer[sizeofbuffer] != '\0')
		sizeofbuffer++;
	while (src[sizeofsrc] != '\0')
		sizeofsrc++;
	if (size == 0)
		return (sizeofsrc);
	j = sizeofbuffer;
	i = 0;
	while (j < size - 1 && src[i] != '\0')
	{
		buffer[j] = src[i];
		j++;
		i++;
	}
	buffer[j] = '\0';
	if (sizeofbuffer >= size)
		sizeofbuffer = size;
	return (sizeofbuffer + sizeofsrc);
}
