/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 04:34:14 by auplisas          #+#    #+#             */
/*   Updated: 2024/10/12 22:18:11 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>
#include <string.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*array;

	i = 0;
	if (start >= ft_strlen(s))
	{
		return (ft_strdup(""));
	}
	if (len > ft_strlen(s) - start)
	{
		len = ft_strlen(s) - start;
	}
	array = (char *)malloc(len + 1);
	if (array == NULL)
	{
		return (NULL);
	}
	while (i < len && s[start + i] != '\0')
	{
		array[i] = s[i + start];
		i++;
	}
	array[i] = '\0';
	return (array);
}

// int	main(void)
// {
// 	const char *str = "hola";
// 	int start = 2;
// 	size_t len = 30;

// 	// Extract the substring
// 	char *result = ft_substr(str, start, len);
// 	printf("%s", result);
// }