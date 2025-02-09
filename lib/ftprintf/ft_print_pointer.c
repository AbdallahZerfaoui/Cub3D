/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:34:25 by auplisas          #+#    #+#             */
/*   Updated: 2024/11/16 03:23:19 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	count_long_hex_digits(unsigned long long num)
{
	unsigned long long	temp;
	int					i;

	temp = num;
	i = 0;
	while (temp > 0)
	{
		temp /= 16;
		i++;
	}
	return (i);
}

void	print_long_hex(unsigned long long num, int *count)
{
	int			i;
	int			temp;
	const char	*hex_digits;
	char		*array_of_hexed_digits;

	i = count_long_hex_digits(num);
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

void	print_pointer(void *ptr, int *count)
{
	unsigned long long	ptr_unsigned;

	ft_printf_putstr_fd("0x", 1, count);
	ptr_unsigned = (unsigned long long)ptr;
	if (ptr_unsigned == 0)
		ft_printf_putchar_fd('0', 1, count);
	else
		print_long_hex((unsigned long long)ptr_unsigned, count);
}
