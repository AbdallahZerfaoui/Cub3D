/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:41:55 by auplisas          #+#    #+#             */
/*   Updated: 2024/10/10 16:22:54 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	haystackindex;
	size_t	needleindex;
	size_t	needlesize;

	haystackindex = 0;
	needleindex = 0;
	needlesize = ft_strlen(needle);
	if (*needle == '\0')
		return ((char *)haystack);
	while (haystack[haystackindex] != '\0' && haystackindex < len)
	{
		if (haystack[haystackindex] == needle[needleindex])
			needleindex++;
		else
		{
			haystackindex -= needleindex;
			needleindex = 0;
		}
		if (needlesize == needleindex)
			return ((char *)&haystack[haystackindex - needleindex + 1]);
		haystackindex++;
	}
	return (0);
}
