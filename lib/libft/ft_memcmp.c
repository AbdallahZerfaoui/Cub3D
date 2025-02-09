/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:21:22 by auplisas          #+#    #+#             */
/*   Updated: 2024/10/09 22:38:00 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

int	ft_memcmp(const void *src1, const void *src2, size_t n)
{
	int			i;
	const char	*ptr1;
	const char	*ptr2;

	i = 0;
	ptr1 = (const char *)src1;
	ptr2 = (const char *)src2;
	while (n > 0)
	{
		if (ptr1[i] == ptr2[i])
		{
			i++;
		}
		else
		{
			return ((unsigned char)ptr1[i] - (unsigned char)ptr2[i]);
		}
		n--;
	}
	return (0);
}

// int	main(void)
// {
// 	char str1[15]="abcdef";
// 	char str2[15]="ABCDEF";
// 	int ret;

// 	ret = memcmp(str1, str2, 5);
// 	printf("Result:%d", ret);

// 	return (0);
// }