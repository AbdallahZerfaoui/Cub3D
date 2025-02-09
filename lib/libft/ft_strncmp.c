/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:34:02 by auplisas          #+#    #+#             */
/*   Updated: 2024/11/09 03:18:44 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
#include <string.h>

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	int				i;

	i = 0;
	while (n > 0 && (str1[i] != '\0' || str2[i] != '\0'))
	{
		if (str1[i] == str2[i])
		{
			i++;
		}
		else
		{
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		}
		n--;
	}
	return (0);
}
// int	main(void)
// {
// 	char	str1[20] = "\200";
// 	char	str2[20] = "\0";

// 	// printf("Value is %d:", ft_strncmp(str1, str2, 3));
// 	printf("Value is: %d", ft_strncmp(str1, str2, 1));
// 	return (0);
// }
