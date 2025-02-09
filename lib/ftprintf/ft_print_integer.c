/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_integer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:31:21 by auplisas          #+#    #+#             */
/*   Updated: 2024/11/16 03:23:27 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	count_n(int num)
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

void	handle_min_max(int n, int fd, int *count)
{
	if (n < -2147483647)
	{
		ft_printf_putstr_fd("-2147483648", fd, count);
		return ;
	}
	else if (n == 2147483647)
	{
		ft_printf_putstr_fd("2147483647", fd, count);
		return ;
	}
}

void	digit_to_string(char *array_of_digits, int n, int digit_count)
{
	int	i;

	i = 0;
	while (i < digit_count)
	{
		array_of_digits[i] = (n % 10) + '0';
		n /= 10;
		i++;
	}
	array_of_digits[i] = '\0';
}

void	ft_putnbr_fd(int n, int fd, int *count)
{
	char	*array_of_digits;
	int		negative;
	int		i;

	negative = 0;
	i = count_n(n);
	if (n < 0)
	{
		negative = 1;
		n = -n;
	}
	array_of_digits = ft_calloc(i + negative + 1, sizeof(char));
	if (!array_of_digits)
	{
		*count = -1;
		return ;
	}
	digit_to_string(array_of_digits, n, i);
	if (negative == 1)
		ft_printf_putchar_fd('-', 1, count);
	while (i--)
		ft_printf_putchar_fd(array_of_digits[i], fd, count);
	free(array_of_digits);
}

void	print_integer(va_list args, int *count)
{
	int	i;

	i = va_arg(args, int);
	if (i < -2147483647 || i == 2147483647)
		return (handle_min_max(i, 1, count));
	else
		ft_putnbr_fd(i, 1, count);
}
