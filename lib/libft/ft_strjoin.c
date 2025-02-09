/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:57:40 by auplisas          #+#    #+#             */
/*   Updated: 2024/11/13 22:47:41 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *prefix, char const *suffix)
{
	char	*array;
	size_t	prefixlength;
	size_t	suffixlength;
	size_t	i;

	prefixlength = ft_strlen(prefix);
	suffixlength = ft_strlen(suffix);
	i = 0;
	array = (char *)malloc(prefixlength + suffixlength + 1);
	if (array == NULL)
		return (NULL);
	while (i < (prefixlength))
	{
		array[i] = prefix[i];
		i++;
	}
	while (i < (prefixlength + suffixlength))
	{
		array[i] = suffix[i - prefixlength];
		i++;
	}
	array[i] = '\0';
	return (array);
}

// int	main(void)
// {
// 	char *result;nof
// 	result = ft_strjoin("", "s");
// 	printf("%s", result);
// 	return (0);
// }