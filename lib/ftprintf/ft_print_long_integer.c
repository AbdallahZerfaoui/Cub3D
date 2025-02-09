/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_long_integer.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:33:38 by auplisas          #+#    #+#             */
/*   Updated: 2024/11/16 03:24:14 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	count_n_long(unsigned int num)
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

void	long_digit_to_string(char *array_of_digits, unsigned long n,
		int digit_count)
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

void	ft_long_putnbr_fd(unsigned int n, int fd, int *count)
{
	int		i;
	char	*array_of_digits;
	int		j;

	j = 0;
	i = count_n_long(n);
	array_of_digits = ft_calloc(i + 1, sizeof(char));
	if (!array_of_digits)
	{
		*count = -1;
		return ;
	}
	long_digit_to_string(array_of_digits, n, i);
	while (array_of_digits[j] != '\0')
		j++;
	while (j--)
		ft_printf_putchar_fd(array_of_digits[j], fd, count);
	free(array_of_digits);
}
