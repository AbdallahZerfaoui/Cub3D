/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:23:48 by auplisas          #+#    #+#             */
/*   Updated: 2024/10/11 21:16:43 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*ptr1;
	char	*ptr2;

	if (!dst && !src)
	{
		return (NULL);
	}
	ptr1 = (char *)dst;
	ptr2 = (char *)src;
	while (n--)
	{
		*ptr1 = *ptr2;
		ptr1++;
		ptr2++;
	}
	return (dst);
}
