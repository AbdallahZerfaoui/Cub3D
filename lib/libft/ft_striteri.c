/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 20:14:18 by auplisas          #+#    #+#             */
/*   Updated: 2024/10/11 21:30:02 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int	str_len;
	int	i;

	str_len = ft_strlen(s);
	i = 0;
	while (i < str_len)
	{
		f(i, &s[i]);
		i++;
	}
}

// int	main(void)
// {
// 	return (0);
// }