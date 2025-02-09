/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 03:08:35 by auplisas          #+#    #+#             */
/*   Updated: 2024/10/10 22:09:21 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// #include <stdio.h>
// #include <stdlib.h>

// void	*ft_memset(void *s, int c, size_t n)
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
// int	main(void)
// {
// 	int n = 2;
// 	int *array;

// 	// use calloc function to allocate the memory
// 	array = (int *)ft_calloc(n, sizeof(int));

// 	if (array == NULL)
// 	{
// 		fprintf(stderr, "Memory allocation failed!\n");
// 		return (1);
// 	}

// 	// Display the array value
// 	printf("Array elements after calloc: ");
// 	for (int i = 0; i < n; i++)
// 	{
// 		printf("%d ", array[i]);
// 	}
// 	printf("\n");

// 	// free the allocated memory
// 	free(array);
// 	return (0);
// }