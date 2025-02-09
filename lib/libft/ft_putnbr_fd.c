/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 22:54:30 by auplisas          #+#    #+#             */
/*   Updated: 2024/10/14 18:51:39 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

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

void	handle_min_max(int n, int fd)
{
	if (n < -2147483647)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	else if (n == 2147483647)
	{
		write(fd, "2147483647", 10);
		return ;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	char	array_of_digits[11];
	int		negative;
	int		i;

	negative = 0;
	i = count_n(n);
	if (n < -2147483647 || n == 2147483647)
	{
		handle_min_max(n, fd);
		return ;
	}
	else
	{
		if (n < 0)
		{
			negative = 1;
			n = -n;
		}
		digit_to_string(array_of_digits, n, i);
		if (negative == 1)
			write(fd, "-", 1);
	}
	while (i--)
		write(fd, &array_of_digits[i], 1);
}
