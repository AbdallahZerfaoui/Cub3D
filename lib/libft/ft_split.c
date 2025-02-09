/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 23:13:38 by auplisas          #+#    #+#             */
/*   Updated: 2024/10/13 01:08:15 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

int	countrows(char const *src, char delimiter)
{
	int	count;
	int	inrow;
	int	i;

	count = 0;
	inrow = 0;
	i = 0;
	while (src[i] != '\0')
	{
		if (src[i] == delimiter)
		{
			if (inrow)
			{
				count++;
				inrow = 0;
			}
		}
		else
			inrow = 1;
		i++;
	}
	if (inrow)
		count++;
	return (count);
}

char	**free_all(char **parentarray, int arrayindex)
{
	int	j;

	j = 0;
	while (j < arrayindex)
	{
		free(parentarray[j]);
		j++;
	}
	free(parentarray);
	return (NULL);
}

char	*allocate_and_copy(const char *s, int startindex, int count)
{
	char	*subarray;

	subarray = (char *)malloc(sizeof(char) * (count + 1));
	if (subarray == NULL)
		return (NULL);
	ft_memcpy(subarray, &s[startindex], count);
	subarray[count] = '\0';
	return (subarray);
}

char	**str_div_logic(char **parentarray, const char *s, char c, int ar_index)
{
	int	i;
	int	count;
	int	startindex;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			startindex = i;
			while (s[i] != '\0' && s[i++] != c)
				count++;
			parentarray[ar_index] = allocate_and_copy(s, startindex, count);
			if (parentarray[ar_index++] == NULL)
				return (free_all(parentarray, ar_index));
			count = 0;
		}
		else
			i++;
	}
	return (parentarray);
}

char	**ft_split(char const *s, char c)
{
	char	**parentarray;
	int		ar_index;

	if (s == NULL)
	{
		return (NULL);
	}
	ar_index = 0;
	parentarray = (char **)malloc(sizeof(char *) * (countrows(s, c) + 1));
	if (parentarray == NULL)
	{
		return (NULL);
	}
	if (str_div_logic(parentarray, s, c, ar_index) == NULL)
	{
		return (NULL);
	}
	parentarray[countrows(s, c)] = NULL;
	return (parentarray);
}

// int	main(void)
// {
// 	char **result;
// 	int i;
// 	char src[] = "hello";
// 	char delimiter = ' ';

// 	result = ft_split("hello!", 32:' ');
// 	if (result)
// 	{
// 		i = 0;
// 		while (result[i])
// 		{
// 			printf("result[%d] = %s\n", i, result[i]);
// 			i++;
// 		}
// 		// Free the allocated memory
// 		i = 0;
// 		while (result[i])
// 		{
// 			free(result[i]);
// 			i++;
// 		}
// 		free(result);
// 	}
// 	return (0);
// }
