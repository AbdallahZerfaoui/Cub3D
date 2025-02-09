/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:04:38 by auplisas          #+#    #+#             */
/*   Updated: 2024/10/10 21:51:12 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

int	containschar(char const *set, char target)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == target)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

char	*returnnullifallset(void)
{
	char	*array;

	array = (char *)malloc(1);
	if (array != NULL)
	{
		array[0] = '\0';
	}
	return (array);
}

char	*ft_strtrim(char const *src, char const *set)
{
	char	*array;
	size_t	firstindex;
	size_t	lastindex;
	int		i;

	firstindex = 0;
	lastindex = ft_strlen(src);
	while (src[firstindex] != '\0' && containschar(set, src[firstindex]) == 1)
		firstindex++;
	if (firstindex == lastindex)
		return (returnnullifallset());
	lastindex--;
	while (lastindex > firstindex && containschar(set, src[lastindex]) == 1)
		lastindex--;
	array = (char *)malloc(lastindex - firstindex + 2);
	if (array == NULL)
		return (NULL);
	i = 0;
	while (firstindex <= lastindex)
		array[i++] = src[firstindex++];
	array[i] = '\0';
	return (array);
}
