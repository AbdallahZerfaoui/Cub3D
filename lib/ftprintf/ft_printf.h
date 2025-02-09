/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 18:00:38 by auplisas          #+#    #+#             */
/*   Updated: 2024/11/16 03:23:11 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

void	*ft_calloc(size_t count, size_t size);
void	int_to_hex(unsigned int num, int uppercase_hex, int *count);
void	print_integer(va_list args, int *count);
void	ft_long_putnbr_fd(unsigned int n, int fd, int *count);
void	print_pointer(void *ptr, int *count);
void	ft_printf_putchar_fd(char c, int fd, int *count);
void	ft_printf_putstr_fd(char *s, int fd, int *count);
int		ft_printf(const char *format, ...);

#endif