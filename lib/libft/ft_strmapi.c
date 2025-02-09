/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 19:19:42 by auplisas          #+#    #+#             */
/*   Updated: 2024/10/11 20:13:41 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*array_of_str;
	int		str_len;
	int		i;

	str_len = ft_strlen(s);
	i = 0;
	array_of_str = (char *)malloc(sizeof(char) * (str_len + 1));
	if (array_of_str == NULL)
	{
		return (NULL);
	}
	while (i < str_len)
	{
		array_of_str[i] = f(i, s[i]);
		i++;
	}
	array_of_str[i] = '\0';
	return (array_of_str);
}
