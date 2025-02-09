/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:36:46 by auplisas          #+#    #+#             */
/*   Updated: 2024/10/10 04:59:04 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// #include <stdio.h>
// #include <string.h>

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char		*ptr1;
	const char	*ptr2;

	ptr1 = dst;
	ptr2 = src;
	if (!dst && !src)
		return (NULL);
	if (dst < src)
	{
		while (n--)
		{
			*ptr1++ = *ptr2++;
		}
	}
	else
	{
		while (n--)
		{
			ptr1[n] = ptr2[n];
		}
	}
	return (dst);
}

// int	main(void)
// {
// 	char dest_str[] = "Hello, World!";
// 	const char src_str[] = "Hello, World!";
// 	printf("Before memmove dest = %s, src = %s\n", dest_str, src_str);
// 	ft_memmove(dest_str, src_str + 3, 4);
// 	printf("After memmove dest = %s, src = %s\n", dest_str, src_str);
// 	return (0);
// }