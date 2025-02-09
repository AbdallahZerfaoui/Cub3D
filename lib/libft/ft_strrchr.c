/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:14:05 by auplisas          #+#    #+#             */
/*   Updated: 2024/10/09 17:31:24 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// #include <stdio.h>
// #include <string.h>

char	*ft_strrchr(char *str, char c)
{
	int	i;

	i = ft_strlen(str);
	while (i > -1)
	{
		if (str[i] == c)
		{
			return ((char *)&str[i]);
		}
		i--;
	}
	if (c == '\0')
	{
		return ((char *)&str[i]);
	}
	return (NULL);
}

// int	main(void)
// {
// 	char str[] = "geliamelias";
// 	// "ch" is search string
// 	// char ch = 'a';
// 	// char *ret;
// 	// ret = ft_strrchr(str, ch);
// 	// // ret = strchr(str, ch);
// 	// printf("String is %s\n", ret);
// 	return (0);
// }