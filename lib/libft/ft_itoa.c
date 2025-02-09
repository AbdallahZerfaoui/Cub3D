/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 05:16:09 by auplisas          #+#    #+#             */
/*   Updated: 2024/10/11 23:50:22 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

void	reverse_array(char *array_of_str)
{
	int		i;
	int		j;
	char	temp;

	i = 0;
	j = ft_strlen(array_of_str) - 1;
	while (i < j)
	{
		temp = array_of_str[i];
		array_of_str[i] = array_of_str[j];
		array_of_str[j] = temp;
		i++;
		j--;
	}
}

int	count_digits(int num)
{
	int	count;

	count = 0;
	if (num < 0)
		num = -num;
	if (num == 0)
		return (1);
	while (num != 0)
	{
		num /= 10;
		count++;
	}
	return (count);
}

void	add_digits_to_ar(int n, char *array_of_str, int digit_amount)
{
	int	i;
	int	negative;

	i = 0;
	negative = 0;
	if (n < 0)
	{
		negative = 1;
		n = -n;
	}
	while (i < digit_amount)
	{
		array_of_str[i] = (n % 10) + '0';
		n /= 10;
		i++;
	}
	if (negative == 1)
	{
		array_of_str[i] = '-';
		i++;
	}
}

char	*ft_itoa(int n)
{
	char	*array_of_str;
	int		bytes;
	int		digit_amount;

	digit_amount = count_digits(n);
	bytes = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 2147483647)
		return (ft_strdup("2147483647"));
	if (n < 0)
	{
		bytes = 1;
	}
	array_of_str = (char *)ft_calloc(digit_amount + bytes + 1, sizeof(char));
	if (array_of_str == NULL)
	{
		return (NULL);
	}
	add_digits_to_ar(n, array_of_str, digit_amount);
	reverse_array(array_of_str);
	return (array_of_str);
}

// int	main(void)
// {
// 	// printf("%d", countDigits(-2420));
// 	printf("%s", ft_itoa(23));
// 	// ft_itoa(243);
// 	return (0);
// }