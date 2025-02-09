/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:24:06 by auplisas          #+#    #+#             */
/*   Updated: 2024/10/10 17:08:05 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <string.h>
#include "libft.h"

char	*ft_strchr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
		{
			return ((char *)&str[i]);
		}
		i++;
	}
	if (c == '\0')
	{
		return ((char *)&str[i]);
	}
	return (NULL);
}

// int	main(void)
// {
// 	char str[] = "";
// 	// "ch" is search string
// 	char ch = '\0';
// 	char *ret;
// 	ret = ft_strchr(str, ch);
// 	// ret = strchr(str, ch);
// 	printf("String is %s\n", ret);
// 	return (0);
// }