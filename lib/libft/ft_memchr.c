/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:52:15 by auplisas          #+#    #+#             */
/*   Updated: 2024/10/10 22:09:55 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// #include <stdio.h>
// #include <string.h>

void	*ft_memchr(const void *str, int c, size_t n)
{
	const char	*ptr;

	ptr = (const char *)str;
	while (n--)
	{
		if (*ptr == (char)c)
		{
			return ((void *)ptr);
		}
		ptr++;
	}
	return (NULL);
}

// int	main(void)
// {
// 	const char str[] = "Tutorialspoint";
// 	const char ch = 'p';
// 	char *ret;
// 	// ft_memchr(str, ch, strlen(str));
// 	ret = ft_memchr(str, ch, strlen(str));
// 	printf("Answer:%s\n", ret);
// 	return (0);
// }