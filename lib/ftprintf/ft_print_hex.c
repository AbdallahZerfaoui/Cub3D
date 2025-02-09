/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:33:10 by auplisas          #+#    #+#             */
/*   Updated: 2024/11/16 03:23:31 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	count_hex_digits(unsigned int num)
{
	unsigned int	temp;
	int				i;

	temp = num;
	i = 0;
	while (temp > 0)
	{
		temp /= 16;
		i++;
	}
	return (i);
}

void	print_hex(unsigned int num, int uppercase_hex, int *count)
{
	int			i;
	int			temp;
	const char	*hex_digits;
	char		*array_of_hexed_digits;

	i = count_hex_digits(num);
	if (uppercase_hex == 1)
		hex_digits = "0123456789ABCDEF";
	else
		hex_digits = "0123456789abcdef";
	array_of_hexed_digits = ft_calloc(i + 1, sizeof(char));
	if (!array_of_hexed_digits)
	{
		*count = -1;
		return ;
	}
	i--;
	while (num > 0)
	{
		temp = num % 16;
		num /= 16;
		array_of_hexed_digits[i--] = hex_digits[temp];
	}
	ft_printf_putstr_fd(array_of_hexed_digits, 1, count);
	free(array_of_hexed_digits);
}

void	int_to_hex(unsigned int num, int uppercase_hex, int *count)
{
	if (num == 0)
		ft_printf_putchar_fd('0', 1, count);
	else
		print_hex((unsigned int)num, uppercase_hex, count);
}
