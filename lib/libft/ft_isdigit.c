/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:21:19 by auplisas          #+#    #+#             */
/*   Updated: 2024/10/08 01:00:46 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
#include "libft.h"

int	ft_isdigit(int ch)
{
	if ((ch >= '0' && ch <= '9'))
	{
		return (1);
	}
	return (0);
}

// int	main(void)
// {
// 	printf("%d\n", ft_isdigit('a'));
// 	return (0);
// }