/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 22:54:16 by auplisas          #+#    #+#             */
/*   Updated: 2024/11/16 03:23:14 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	select_input_type(const char *format, va_list args, int i, int *count)
{
	while (format[i] != '\0')
	{
		if (format[i] == '%' && format[i + 1] == 'c')
			return (ft_printf_putchar_fd(va_arg(args, int), 1, count));
		else if (format[i] == '%' && format[i + 1] == 's')
			return (ft_printf_putstr_fd(va_arg(args, char *), 1, count));
		else if (format[i] == '%' && format[i + 1] == 'p')
			return (print_pointer(va_arg(args, void *), count));
		else if (format[i] == '%' && format[i + 1] == 'd')
			return (print_integer(args, count));
		else if (format[i] == '%' && format[i + 1] == 'i')
			return (print_integer(args, count));
		else if (format[i] == '%' && format[i + 1] == 'u')
			return (ft_long_putnbr_fd(va_arg(args, unsigned int), 1, count));
		else if (format[i] == '%' && format[i + 1] == 'x')
			return (int_to_hex(va_arg(args, unsigned long), 0, count));
		else if (format[i] == '%' && format[i + 1] == 'X')
			return (int_to_hex(va_arg(args, unsigned long), 1, count));
		else if (format[i] == '%' && format[i + 1] == '%')
			return (ft_printf_putchar_fd('%', 1, count));
		else
			return ;
		i++;
	}
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		count;
	va_list	args;

	i = 0;
	count = 0;
	va_start(args, format);
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			select_input_type(format, args, i, &count);
			i++;
		}
		else
			ft_printf_putchar_fd(format[i], 1, &count);
		i++;
	}
	va_end(args);
	return (count);
}

// int	main(void)
// {
// 	ft_printf("PRINT IT: %x\n", 10);
// 	printf("\nCHARS: %d\n", ft_printf("\001\002\007\v\010\f\r\n"));
// 	return (0);
// }
