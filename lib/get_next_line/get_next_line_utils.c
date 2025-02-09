/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:58:57 by macbook           #+#    #+#             */
/*   Updated: 2024/11/13 22:25:49 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_gnl(const char *c)
{
	size_t	i;

	i = 0;
	while (c[i] != '\0')
		i++;
	return (i);
}

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
			*ptr1++ = *ptr2++;
	}
	else
	{
		while (n--)
			ptr1[n] = ptr2[n];
	}
	return (dst);
}

char	*ft_strchr_gnl(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return ((char *)&str[i]);
		i++;
	}
	if (c == '\0')
		return ((char *)&str[i]);
	return (NULL);
}

char	*ft_strdup_gnl(const char *src)
{
	size_t	i;
	char	*array;

	i = ft_strlen_gnl(src);
	array = (char *)malloc(sizeof(char) * (i + 1));
	if (array == NULL)
		return (NULL);
	ft_memmove(array, src, i + 1);
	array[i] = '\0';
	return (array);
}

char	*ft_substr_gnl(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*array;

	i = 0;
	if (start >= ft_strlen_gnl(s))
		return (ft_strdup_gnl(""));
	if (len > ft_strlen_gnl(s) - start)
		len = ft_strlen_gnl(s) - start;
	array = (char *)malloc(len + 1);
	if (array == NULL)
		return (NULL);
	while (i < len && s[start + i] != '\0')
	{
		array[i] = s[i + start];
		i++;
	}
	array[i] = '\0';
	return (array);
}
