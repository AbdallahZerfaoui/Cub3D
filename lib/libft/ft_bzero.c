/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 00:12:20 by auplisas          #+#    #+#             */
/*   Updated: 2024/10/12 00:45:08 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>
// #include <string.h>

// void	*ft_memsets(void *s, int c, size_t n)
// {
// 	unsigned char	*ptr;

// 	ptr = (unsigned char *)s;
// 	while (n--)
// 	{
// 		*ptr = (unsigned char)c;
// 		ptr++;
// 	}
// 	return (s);
// }

void	ft_bzero(void *dst, size_t n)
{
	ft_memset(dst, '\0', n);
}

// int	main(void)
// {
// 	char	str[50] = "GeeksForGeeks is for programming geeks.";

// 	ft_bzero(str, 8 * sizeof(char));
// 	printf("%s", str);
// 	printf("%s", "zazamaza");
// 	return (0);
// }
